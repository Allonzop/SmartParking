# 🧾 Scanner de tickets de caisse

Petite application web perso pour **scanner tes tickets de caisse / factures**, les
ranger dans **Google Drive** et remplir automatiquement un **Google Sheet**.

Pour chaque ticket :

1. **Scan noir & blanc rogné automatiquement** — depuis une photo (appareil photo
   du téléphone) ou un PDF.
2. **Envoi du scan dans ton Google Drive.**
3. **Ajout d'une ligne dans un Google Sheet** avec les propriétés lues sur le
   ticket (marchand, date, total, TVA, catégorie…) **et le lien vers le scan**.

100 % gratuit, **aucune clé API**, aucun serveur à héberger.

---

## ⚙️ Comment ça marche

| Étape | Techno | Où ça tourne |
|------|--------|--------------|
| Rognage auto + noir & blanc | **OpenCV.js** (repli JS pur si indispo) | Dans ton navigateur |
| Lecture du ticket (OCR français) | **Tesseract.js** | Dans ton navigateur |
| Lecture des PDF | **pdf.js** | Dans ton navigateur |
| Stockage Drive + écriture Sheet | **Google Apps Script** | Hébergé par Google (gratuit) |

Le traitement de l'image et l'OCR se font **entièrement dans le navigateur** :
tes tickets ne transitent par aucun service tiers. Seuls le scan final et les
champs partent vers **ton** Drive / Sheet via Apps Script.

> ⚠️ L'OCR gratuit se trompe parfois (tickets froissés, mal cadrés…). **Tous les
> champs sont modifiables** avant l'envoi : tu corriges en 2 secondes.

---

## 🚀 Installation (≈ 5 minutes)

### Méthode A — Copier-coller dans Apps Script (la plus simple)

1. Va sur **[script.google.com](https://script.google.com)** → **Nouveau projet**.
2. Renomme le projet (ex. « Scanner tickets »).
3. **Fichier `Code.gs`** : remplace tout le contenu par celui de
   [`apps-script/Code.gs`](apps-script/Code.gs).
4. **Ajoute un fichier HTML** : clique `+` → **HTML**, nomme-le **`Index`**
   (exactement, sans extension), puis colle le contenu de
   [`apps-script/Index.html`](apps-script/Index.html).
5. *(Optionnel mais conseillé)* Active le manifeste : ⚙️ **Paramètres du projet**
   → coche **« Afficher le fichier manifeste `appsscript.json` »**, puis colle le
   contenu de [`apps-script/appsscript.json`](apps-script/appsscript.json).
6. **Déploie** : bouton **Déployer** → **Nouveau déploiement** → type
   **Application Web**.
   - *Exécuter en tant que* : **Moi**
   - *Qui a accès* : **Seul moi-même** (usage perso privé)
   - Clique **Déployer** et **autorise** les accès demandés (Drive + Sheets).
7. Copie l'**URL de l'application web** proposée : c'est le lien de ton scanner.

### Méthode B — Avec `clasp` (ligne de commande)

```bash
npm install -g @google/clasp
clasp login
cd receipt-scanner/apps-script
clasp create --type webapp --title "Scanner tickets"
clasp push
clasp deploy
```

(Un exemple de `.clasp.json` est fourni : [`apps-script/.clasp.json.example`](apps-script/.clasp.json.example).)

---

## 📱 Utilisation

1. Ouvre l'**URL de l'application web** sur ton téléphone.
   *Astuce : « Ajouter à l'écran d'accueil » pour l'avoir comme une appli.*
2. **Prendre une photo** (ouvre l'appareil photo) ou **Photo / PDF existant**.
3. L'app génère le **scan noir & blanc rogné**, puis lit le ticket.
4. Vérifie / corrige les **propriétés** (marchand, date, total, catégorie…).
5. **Envoyer vers Drive + Sheet** → tu obtiens les liens du scan et du tableau.

Le dossier Drive **« Tickets scannés »** et le tableau **« Tickets de caisse »**
sont **créés automatiquement** à la première utilisation.

---

## 🎛️ Options

- **Cibler un dossier / un tableau existants** : dans Apps Script →
  ⚙️ **Paramètres du projet** → **Propriétés du script**, ajoute :
  - `FOLDER_ID` = l'ID du dossier Drive (dans son URL après `folders/`)
  - `SHEET_ID` = l'ID du Google Sheet (dans son URL après `/d/`)
- **Rendre les scans accessibles par lien** (par défaut ils restent privés) :
  dé-commente la ligne `setSharing(...)` dans `Code.gs`.
- **Colonnes du tableau** : `Date d'ajout · Date ticket · Marchand · Catégorie ·
  Total · Devise · TVA · N° ticket · Lien scan · Texte brut`. Modifie la constante
  `ENTETES` (et la fonction `saveReceipt`) dans `Code.gs` pour les adapter.

---

## 🔧 Dépannage

| Problème | Solution |
|----------|----------|
| « google.script.run indisponible » | Ouvre l'app via l'**URL du web app**, pas en fichier local. |
| Le rognage n'est pas parfait | Cadre le ticket sur un **fond contrasté**, ou décoche **Rognage auto**. |
| OCR lent la 1re fois | Les bibliothèques (OpenCV/Tesseract) se téléchargent une fois puis sont mises en cache. |
| Un champ est faux | Corrige-le dans le formulaire avant l'envoi. |
| Après modif du code | Redéploie : **Déployer → Gérer les déploiements → ✏️ → Nouvelle version**. |

---

## 💡 Envie de plus de précision plus tard ?

L'OCR gratuit est correct mais imparfait. Pour une lecture beaucoup plus fiable
sur des tickets très variés, on peut brancher l'extraction sur **Claude Vision**
(l'IA lit le ticket et renvoie les champs en JSON). Ça nécessite une clé API
Claude et un petit coût par ticket. L'architecture actuelle est prête pour cette
évolution : il suffirait de remplacer `runOCR` + `parseReceipt` par un appel à
Claude (côté Apps Script via `UrlFetchApp`, pour garder la clé secrète).
Demande-le si tu veux passer à cette version.
