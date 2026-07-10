/**
 * Scanner de tickets de caisse — Backend Google Apps Script
 * -----------------------------------------------------------
 * Rôle :
 *   1. Servir la page web de l'application (doGet -> Index.html)
 *   2. Recevoir un scan (image N&B rognée) + les propriétés lues sur le ticket
 *   3. Enregistrer le scan dans un dossier Google Drive
 *   4. Ajouter une ligne dans un Google Sheet avec les propriétés + le lien du scan
 *
 * Le dossier Drive et la feuille sont créés automatiquement à la première
 * utilisation. Pour cibler un dossier / une feuille existants, renseigne les
 * propriétés de script FOLDER_ID et SHEET_ID (voir README).
 */

var PROPS = PropertiesService.getScriptProperties();

var NOM_DOSSIER = 'Tickets scannés';
var NOM_FEUILLE = 'Tickets de caisse';

var ENTETES = [
  "Date d'ajout", 'Date ticket', 'Marchand', 'Catégorie',
  'Total', 'Devise', 'TVA', 'N° ticket', 'Lien scan', 'Texte brut'
];

/** Sert la page de l'application. */
function doGet() {
  return HtmlService.createHtmlOutputFromFile('Index')
    .setTitle('Scanner de tickets')
    .addMetaTag('viewport', 'width=device-width, initial-scale=1, maximum-scale=1')
    .setXFrameOptionsMode(HtmlService.XFrameOptionsMode.ALLOWALL);
}

/** Récupère (ou crée) le dossier Drive de destination des scans. */
function getDossier_() {
  var id = PROPS.getProperty('FOLDER_ID');
  if (id) {
    try { return DriveApp.getFolderById(id); } catch (e) { /* id invalide -> on recrée */ }
  }
  var dossier = DriveApp.createFolder(NOM_DOSSIER);
  PROPS.setProperty('FOLDER_ID', dossier.getId());
  return dossier;
}

/** Récupère (ou crée) la feuille Google Sheet, en garantissant la ligne d'en-tête. */
function getFeuille_() {
  var ss = null;
  var id = PROPS.getProperty('SHEET_ID');
  if (id) {
    try { ss = SpreadsheetApp.openById(id); } catch (e) { ss = null; }
  }
  if (!ss) {
    ss = SpreadsheetApp.create(NOM_FEUILLE);
    PROPS.setProperty('SHEET_ID', ss.getId());
  }
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
 * Appelé depuis la page via google.script.run.
 *
 * @param {Object} payload
 *   payload.imageBase64 {string}  Image encodée en base64 (sans le préfixe data:)
 *   payload.mimeType    {string}  Ex. "image/png"
 *   payload.filename    {string}  Nom de fichier souhaité
 *   payload.rawText     {string}  Texte OCR brut
 *   payload.fields      {Object}  {date, merchant, category, total, currency, tva, ticketNumber}
 * @return {Object} { ok, url, sheetUrl }
 */
function saveReceipt(payload) {
  if (!payload || !payload.imageBase64) {
    throw new Error('Aucune image reçue.');
  }

  var fields = payload.fields || {};
  var dossier = getDossier_();

  var bytes = Utilities.base64Decode(payload.imageBase64);
  var mime = payload.mimeType || 'image/png';
  var nom = payload.filename || ('ticket-' + Date.now() + '.png');
  var blob = Utilities.newBlob(bytes, mime, nom);
  var fichier = dossier.createFile(blob);

  // Le fichier reste PRIVÉ (visible uniquement par toi). Le lien fonctionne
  // une fois connecté à ton compte Google. Pour rendre les scans accessibles
  // par lien à d'autres personnes, décommente la ligne suivante :
  // fichier.setSharing(DriveApp.Access.ANYONE_WITH_LINK, DriveApp.Permission.VIEW);

  var url = fichier.getUrl();

  var sheet = getFeuille_();
  sheet.appendRow([
    new Date(),
    fields.date || '',
    fields.merchant || '',
    fields.category || '',
    fields.total || '',
    fields.currency || '',
    fields.tva || '',
    fields.ticketNumber || '',
    url,
    payload.rawText || ''
  ]);

  return {
    ok: true,
    url: url,
    sheetUrl: sheet.getParent().getUrl()
  };
}

/** Utilitaire de diagnostic : renvoie les liens du dossier et de la feuille. */
function getLinks() {
  return {
    folderUrl: getDossier_().getUrl(),
    sheetUrl: getFeuille_().getParent().getUrl()
  };
}
