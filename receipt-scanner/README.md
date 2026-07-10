# 🧾 Scanner de tickets de caisse

Application web perso pour **scanner tes tickets de caisse / factures**, les ranger
dans **Google Drive** et remplir automatiquement un **Google Sheet**.

Pour chaque ticket :

1. **Lecture par l'IA (Claude)** — tu prends une photo (ou un PDF). Claude lit
   directement la photo couleur et extrait les informations (marchand, date,
   total, TVA, catégorie, n° ticket).
2. **Rognage automatique** — Claude détecte aussi les **4 coins du ticket** ; le
   scan est rogné tout seul, au bon endroit. Tu peux réajuster à la main si besoin
   (poignées) — mais en général ce n'est pas nécessaire.
3. **Rendu scan couleur** — fond aplati/blanchi, couleurs et netteté préservées
   (pas de noir & blanc destructeur).
4. **Envoi dans Google Drive** + **ajout d'une ligne dans un Google Sheet** avec
   les propriétés **et le lien vers le scan**.

---

## ⚙️ Comment ça marche

| Étape | Techno | Où ça tourne |
|------|--------|--------------|
| Lecture du ticket + détection des coins | **Claude (API)** | Appelé côté serveur par Apps Script |
| Rognage (perspective) + rendu scan couleur | **OpenCV.js** (repli JS si indispo) | Dans ton navigateur |
| Lecture des PDF | **pdf.js** | Dans ton navigateur |
| Stockage Drive + écriture Sheet | **Google Apps Script** | Hébergé par Google (gratuit) |

La clé API Claude est stockée **côté serveur (Apps Script)** et n'est **jamais
exposée dans le navigateur** : la photo est envoyée à Apps Script, qui appelle
Claude avec la clé secrète, puis renvoie les résultats.

---

## 🔑 Obtenir une clé API Claude (indispensable)

> ⚠️ Je ne peux pas fournir de clé : tu dois créer **la tienne** (2 minutes).

1. Va sur **[console.anthropic.com](https://console.anthropic.com)** → crée un compte.
2. **Billing** → ajoute un petit crédit (quelques euros suffisent pour des
   centaines de tickets).
3. **API keys** → **Create Key** → copie la clé (commence par `sk-ant-...`).

**Coût indicatif :** avec le modèle par défaut `claude-opus-4-8`, compter ≈ 1 à
2 centimes par ticket. Pour réduire, tu peux utiliser un modèle moins cher : ajoute
la propriété de script `ANTHROPIC_MODEL` = `claude-haiku-4-5` (beaucoup moins cher,
un peu moins fin) ou `claude-sonnet-5`.

---

## 🚀 Installation (≈ 5 minutes)

### Méthode A — Copier-coller dans Apps Script (la plus simple)

1. Va sur **[script.google.com](https://script.google.com)** → **Nouveau projet**.
2. **`Code.gs`** : remplace tout par le contenu de [`apps-script/Code.gs`](apps-script/Code.gs).
3. **Ajoute un fichier HTML** nommé exactement **`Index`** (`+` → HTML) et colle
   [`apps-script/Index.html`](apps-script/Index.html).
4. ⚙️ **Paramètres du projet** → coche **« Afficher `appsscript.json` »** et colle
   [`apps-script/appsscript.json`](apps-script/appsscript.json)
   (il ajoute le droit d'appeler l'API Claude).
5. ⚙️ **Paramètres du projet** → **Propriétés du script** → **Ajouter** :
   - `ANTHROPIC_API_KEY` = ta clé `sk-ant-...`
   - *(optionnel)* `ANTHROPIC_MODEL` = `claude-haiku-4-5` pour réduire le coût
6. **Déployer** → **Nouveau déploiement** → **Application Web**
   - *Exécuter en tant que* : **Moi**
   - *Qui a accès* : **Seul moi-même**
   - **Déployer**, puis **autorise** les accès (Drive, Sheets, requêtes externes).
7. Copie l'**URL de l'application web** : c'est ton scanner.

### Méthode B — Avec `clasp`

```bash
npm install -g @google/clasp
clasp login
cd apps-script
clasp create --type webapp --title "Scanner tickets"
clasp push
# puis, dans l'éditeur Apps Script : ajoute ANTHROPIC_API_KEY dans les
# Propriétés du script, et déploie en Application Web.
```

---

## 📱 Utilisation

1. Ouvre l'**URL** sur ton téléphone. *(« Ajouter à l'écran d'accueil » pour l'avoir comme une appli.)*
2. **Prendre une photo** ou **Photo / PDF existant**.
3. L'IA lit le ticket **et le rogne automatiquement** → le scan s'affiche.
   *Besoin de corriger le cadrage ? → « Réajuster le rognage » (glisse les coins).*
4. Vérifie / corrige les **propriétés** (tout est modifiable).
5. **Envoyer vers Drive + Sheet** → liens du scan et du tableau.

Le dossier **« Tickets scannés »** et le tableau **« Tickets de caisse »** sont
créés automatiquement à la première utilisation.

---

## 🎛️ Options (Propriétés du script)

| Propriété | Rôle |
|-----------|------|
| `ANTHROPIC_API_KEY` | **Obligatoire.** Ta clé API Claude. |
| `ANTHROPIC_MODEL` | Modèle utilisé (défaut `claude-opus-4-8`). Ex. `claude-haiku-4-5` pour le coût. |
| `FOLDER_ID` | Cibler un dossier Drive existant (ID dans son URL après `folders/`). |
| `SHEET_ID` | Cibler un Google Sheet existant (ID dans son URL après `/d/`). |

- **Rendu du scan** : menu déroulant dans l'app — **Couleur (scan)** /
  **Noir & blanc doux** / **Photo brute**.
- **Rendre les scans partageables par lien** (privés par défaut) : dé-commente la
  ligne `setSharing(...)` dans `Code.gs`.
- **Colonnes du tableau** : `Date d'ajout · Date ticket · Marchand · Catégorie ·
  Total · Devise · TVA · N° ticket · Lien scan`.

---

## 🔧 Dépannage

| Problème | Solution |
|----------|----------|
| « Clé API Claude manquante » | Ajoute `ANTHROPIC_API_KEY` dans les Propriétés du script, puis redéploie. |
| « Clé API refusée (401) » | Clé invalide/expirée, ou crédit épuisé (Billing). |
| « google.script.run indisponible » | Ouvre l'app via l'**URL du web app**, pas en fichier local. |
| Le rognage auto est un peu décalé | « Réajuster le rognage » et glisse les coins (poignées agrandies). |
| Après modif du code | Redéploie : **Déployer → Gérer les déploiements → ✏️ → Nouvelle version**. |
