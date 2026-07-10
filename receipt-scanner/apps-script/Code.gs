/**
 * Scanner de tickets de caisse — Backend Google Apps Script
 * -----------------------------------------------------------
 * Rôle :
 *   1. Servir la page web de l'application (doGet -> Index.html)
 *   2. analyzeReceipt : envoyer la photo à Claude (IA) qui lit le ticket ET
 *      renvoie les 4 coins du ticket pour un rognage automatique fiable.
 *   3. saveReceipt : enregistrer le scan dans Google Drive + ajouter une ligne
 *      dans un Google Sheet avec les propriétés + le lien du scan.
 *
 * ⚙️ CONFIGURATION (Paramètres du projet -> Propriétés du script) :
 *   ANTHROPIC_API_KEY  (obligatoire) : ta clé API Claude (console.anthropic.com)
 *   ANTHROPIC_MODEL    (optionnel)   : modèle, défaut "claude-opus-4-8"
 *   FOLDER_ID          (optionnel)   : dossier Drive existant
 *   SHEET_ID           (optionnel)   : Google Sheet existant
 */

var PROPS = PropertiesService.getScriptProperties();

var NOM_DOSSIER = 'Tickets scannés';
var NOM_FEUILLE = 'Tickets de caisse';
var MODELE_DEFAUT = 'claude-opus-4-8';

var CATEGORIES = [
  'Alimentation / Courses', 'Restauration', 'Carburant', 'Transport',
  'Santé / Pharmacie', 'Vêtements', 'Loisirs', 'Électronique',
  'Maison / Bricolage', 'Services', 'Autre'
];

var ENTETES = [
  "Date d'ajout", 'Date ticket', 'Marchand', 'Catégorie',
  'Total', 'Devise', 'TVA', 'N° ticket', 'Lien scan'
];

/** Sert la page de l'application. */
function doGet() {
  return HtmlService.createHtmlOutputFromFile('Index')
    .setTitle('Scanner de tickets')
    .addMetaTag('viewport', 'width=device-width, initial-scale=1, maximum-scale=1')
    .setXFrameOptionsMode(HtmlService.XFrameOptionsMode.ALLOWALL);
}

/* =======================================================================
   ANALYSE PAR L'IA (Claude)
   ======================================================================= */

/**
 * Envoie l'image à Claude et renvoie les propriétés + les 4 coins du ticket.
 * @param {Object} payload  { imageBase64, mimeType }
 * @return {Object} { ok, fields:{...}, corners:{tl,tr,br,bl} }  (coins en fractions 0..1)
 */
function analyzeReceipt(payload) {
  if (!payload || !payload.imageBase64) throw new Error('Aucune image reçue.');
  var apiKey = PROPS.getProperty('ANTHROPIC_API_KEY');
  if (!apiKey) {
    throw new Error("Clé API Claude manquante. Ajoute la propriété de script « ANTHROPIC_API_KEY » (voir README).");
  }
  var model = PROPS.getProperty('ANTHROPIC_MODEL') || MODELE_DEFAUT;
  var mime = payload.mimeType || 'image/jpeg';

  var prompt =
    "Tu lis un ticket de caisse ou une facture sur la photo. Renvoie les informations demandées.\n" +
    "- date : date du ticket au format JJ/MM/AAAA (chaîne vide si absente).\n" +
    "- total : le MONTANT TOTAL PAYÉ (TTC), au format « 12,34 » (chaîne vide si absent).\n" +
    "- currency : code devise (EUR, USD, GBP, CHF…).\n" +
    "- tva : montant total de TVA au format « 1,23 » (chaîne vide si absent).\n" +
    "- merchant : nom du commerçant/enseigne.\n" +
    "- category : EXACTEMENT l'une de ces valeurs : " + CATEGORIES.join(' | ') + ".\n" +
    "- ticketNumber : numéro de ticket/reçu si présent, sinon chaîne vide.\n" +
    "- corners : les 4 coins du ticket dans l'image, en FRACTIONS de 0 à 1 " +
    "(x = fraction de la largeur depuis la gauche, y = fraction de la hauteur depuis le haut). " +
    "tl = haut-gauche, tr = haut-droite, br = bas-droite, bl = bas-gauche. " +
    "Cadre au plus près du bord du ticket, en excluant l'arrière-plan.";

  var schema = {
    type: 'object',
    properties: {
      merchant: { type: 'string' },
      date: { type: 'string' },
      total: { type: 'string' },
      currency: { type: 'string' },
      tva: { type: 'string' },
      category: { type: 'string' },
      ticketNumber: { type: 'string' },
      corners: {
        type: 'object',
        properties: {
          tl: pointSchema_(), tr: pointSchema_(), br: pointSchema_(), bl: pointSchema_()
        },
        required: ['tl', 'tr', 'br', 'bl'],
        additionalProperties: false
      }
    },
    required: ['merchant', 'date', 'total', 'currency', 'tva', 'category', 'ticketNumber', 'corners'],
    additionalProperties: false
  };

  var body = {
    model: model,
    max_tokens: 1024,
    messages: [{
      role: 'user',
      content: [
        { type: 'image', source: { type: 'base64', media_type: mime, data: payload.imageBase64 } },
        { type: 'text', text: prompt }
      ]
    }],
    output_config: { format: { type: 'json_schema', schema: schema } }
  };

  var resp = UrlFetchApp.fetch('https://api.anthropic.com/v1/messages', {
    method: 'post',
    contentType: 'application/json',
    muteHttpExceptions: true,
    headers: { 'x-api-key': apiKey, 'anthropic-version': '2023-06-01' },
    payload: JSON.stringify(body)
  });

  var code = resp.getResponseCode();
  var raw = resp.getContentText();
  if (code !== 200) {
    var msg = raw;
    try { msg = JSON.parse(raw).error.message; } catch (e) {}
    if (code === 401) throw new Error("Clé API refusée (401). Vérifie ANTHROPIC_API_KEY.");
    throw new Error('Erreur API Claude (' + code + ') : ' + String(msg).slice(0, 300));
  }

  var data = JSON.parse(raw);
  if (data.stop_reason === 'refusal') throw new Error("L'analyse a été refusée par le modèle.");
  var text = '';
  for (var i = 0; i < data.content.length; i++) {
    if (data.content[i].type === 'text') { text = data.content[i].text; break; }
  }
  var parsed = JSON.parse(text);

  return { ok: true, fields: {
      merchant: parsed.merchant || '', date: parsed.date || '', total: parsed.total || '',
      currency: parsed.currency || '', tva: parsed.tva || '',
      category: parsed.category || '', ticketNumber: parsed.ticketNumber || ''
    },
    corners: parsed.corners || null
  };
}

function pointSchema_() {
  return { type: 'object', properties: { x: { type: 'number' }, y: { type: 'number' } }, required: ['x', 'y'], additionalProperties: false };
}

/* =======================================================================
   ENREGISTREMENT (Drive + Sheet)
   ======================================================================= */

function getDossier_() {
  var id = PROPS.getProperty('FOLDER_ID');
  if (id) { try { return DriveApp.getFolderById(id); } catch (e) {} }
  var dossier = DriveApp.createFolder(NOM_DOSSIER);
  PROPS.setProperty('FOLDER_ID', dossier.getId());
  return dossier;
}

function getFeuille_() {
  var ss = null;
  var id = PROPS.getProperty('SHEET_ID');
  if (id) { try { ss = SpreadsheetApp.openById(id); } catch (e) { ss = null; } }
  if (!ss) { ss = SpreadsheetApp.create(NOM_FEUILLE); PROPS.setProperty('SHEET_ID', ss.getId()); }
  var sheet = ss.getSheets()[0];
  if (sheet.getLastRow() === 0) {
    sheet.appendRow(ENTETES);
    sheet.getRange(1, 1, 1, ENTETES.length).setFontWeight('bold');
    sheet.setFrozenRows(1);
  }
  return sheet;
}

/**
 * Enregistre un ticket : image dans Drive + ligne dans le Sheet.
 * @param {Object} payload  { imageBase64, mimeType, filename, fields }
 * @return {Object} { ok, url, sheetUrl }
 */
function saveReceipt(payload) {
  if (!payload || !payload.imageBase64) throw new Error('Aucune image reçue.');
  var fields = payload.fields || {};
  var dossier = getDossier_();

  var blob = Utilities.newBlob(
    Utilities.base64Decode(payload.imageBase64),
    payload.mimeType || 'image/jpeg',
    payload.filename || ('ticket-' + Date.now() + '.jpg')
  );
  var fichier = dossier.createFile(blob);
  // Fichier PRIVÉ par défaut. Pour un lien partageable, décommente :
  // fichier.setSharing(DriveApp.Access.ANYONE_WITH_LINK, DriveApp.Permission.VIEW);
  var url = fichier.getUrl();

  var sheet = getFeuille_();
  sheet.appendRow([
    new Date(), fields.date || '', fields.merchant || '', fields.category || '',
    fields.total || '', fields.currency || '', fields.tva || '', fields.ticketNumber || '', url
  ]);

  return { ok: true, url: url, sheetUrl: sheet.getParent().getUrl() };
}

/** Diagnostic rapide. */
function getLinks() {
  return { folderUrl: getDossier_().getUrl(), sheetUrl: getFeuille_().getParent().getUrl() };
}
