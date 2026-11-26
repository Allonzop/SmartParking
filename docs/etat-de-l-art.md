# État de l'art — Systèmes de Smart Parking

> Travail de groupe réalisé dans le cadre du module *Initiation à la recherche* (ESTP), décembre 2025 — Nalan Tagore, Eric Grandsart, Moussa Nassour, Allonzo Pensabene.  
> 26 articles scientifiques et techniques analysés (2012-2025). Tableau détaillé : [`bibliographie-26-articles.csv`](bibliographie-26-articles.csv).

## INTRODUCTION AU CONCEPT DE SMART PARKING

### Alignement avec les Villes Intelligentes (Smart City)

L’idée de **smart city** émerge au croisement de plusieurs dynamiques : l’urbanisation rapide, la disponibilité croissante des données, la connectivité numérique et le besoin d’optimiser des services publics saturés. Une smart city est généralement définie comme une ville qui mobilise des **technologies numériques**, des **réseaux intelligents** et des **données en temps réel** pour améliorer la qualité de vie, soutenir le développement durable et optimiser la gestion des ressources.

Ce concept s’est construit graduellement :

* **Années 1980–1990 :** premières réflexions sur la “ville numérique” et l’informatisation des services urbains.

* **Années 2000 :** arrivée massive de l’Internet haut débit et des premiers capteurs urbains → naissance du terme “smart city”.

* **Années 2010–2020 :** généralisation de l’IoT et de la mobilité connectée → multiplication des sous-domaines intelligents.

La smart city n’est donc pas un objet unique mais un écosystème, composé de plusieurs “branches” technologiques et fonctionnelles, chacune héritant de traditions différentes (urbanisme, informatique, logistique, design de services, etc.).

### Les grandes branches de la smart city  (« généalogie » conceptuelle)

*Illustration non reproduite ici (droits) — source : <https://www.idemia.com/wp-content/uploads/2021/01/safranidsec_infografik_smartcities_final_new_design-gb.jpg>*

On peut décomposer le concept de ville intelligente en plusieurs domaine, issus de différentes évolutions technologiques :

1\. Smart Mobility  
Hérite des domaines de la logistique, des transports, de la géolocalisation et plus récemment de l’IoT. Elle comprend : transports publics connectés, mobilité partagée,  
gestion du trafic en temps réel et le **smart parking**.

2\. Smart Energy aussi appelé Smart Grid  
Issu des réseaux électriques intelligents(smart grids), de la transition énergétique et du monitoring des consommations. Cette branche induit une électrification majeure du réseau énergétique.

3\. Smart Environment  
Dérive des sciences environnementales et du suivi écologique : qualité de l’air, gestion des déchets, optimisation de l’eau.

4\. Smart Governance  
Ancré dans l’administration numérique et la participation citoyenne.

5\. Smart Living  
Maison connectée, services de santé numériques, culture et loisirs enrichis par la donnée.

#### 6\. Smart Economy (très lié au Big Data)

Transformation numérique des entreprises, économie collaborative, plateformes de services urbains.

**Chaque branche représente une spécialisation née de la convergence entre besoins urbains, technologies disponibles et nouveaux usages.**

---

### Où se situe le Smart Parking dans cette généalogie ?

Le **smart parking** appartient clairement à la branche **Smart Mobility**, mais il se trouve à l'intersection de plusieurs autres domaines :

#### 1\. Smart Mobility (branche principale)

Le smart parking répond aux enjeux de circulation :

* réduire le temps de recherche d’une place (jusqu’à 30 % du trafic en centre-ville selon les études),

* fluidifier la mobilité urbaine,

* diminuer les émissions liées aux voitures en errance.

Il mobilise pour cela des **capteurs**, des **applications mobiles**, l’**analyse de données** et parfois des **systèmes de réservation dynamiques**. 

#### 2\. Définition et Objectifs

Un **système de smart parking** est une solution technologique intégrée qui combine :  
\- Tout d’abord la Détection en temps réel : utilisation de capteurs, caméras ou systèmes d'imagerie pour identifier les places de parking occupées ou libres  
\- Ainsi que la Communication réseau : transmission instantanée des données via IoT, cloud computing ou architecture fog-cloud hybride  
\- Et, Intelligence algorithmique : traitement et analyse des données pour prédire la disponibilité des places et optimiser leur allocation  
\- Interface utilisateur : applications mobiles, affichages numériques et systèmes de guidage pour assister les conducteurs  
\- Pour finir, Gestion et administration : outils de surveillance, contrôle d'accès et paiement électronique pour les opérateurs

### Comment les concepts « smart » sont liés entre eux ?

Les différentes branches de la smart city forment un réseau interconnecté. Le smart parking en est un exemple emblématique : il utilise l’IoT (capteurs), il produit de la data urbaine (taux d’occupation, flux), il alimente des algorithmes de prédiction de trafic, il contribue aux objectifs environnementaux, il s’intègre dans des plateformes de gouvernance centralisées.

On peut donc le considérer comme un nœud où se rencontrent :  
 ➡️ technologies urbaines \+ mobilité \+ durabilité \+ économie de l’attention numérique.

Le smart parking s'inscrit dans une vision plus large des villes intelligentes (Smart Cities), qui utilisent les technologies de l'information et de la communication (TIC) pour améliorer les services urbains, réduire les coûts opérationnels, augmenter l'efficacité énergétique et élever la qualité de vie des citoyens. Le stationnement intelligent représente une composante essentielle de la mobilité urbaine durable, en complément des systèmes de transport intelligent, de la gestion du trafic, et de la gouvernance numérique.

### Contexte et Enjeux Urbains

Le stationnement automobile représente l'un des défis majeurs des villes contemporaines. Selon les études récentes, **30 à 50% des conducteurs consacrent entre 3 et 14 minutes à chercher une place de parking libre**, ce qui génère une congestion supplémentaire, une consommation excessive de carburant, une augmentation des émissions de CO₂ et une dégradation de la qualité de l'air urbain. Aux États-Unis, le coût annuel de cette congestion liée au stationnement est estimé à **13 milliards de dollars** en 2020, avec une projection de croissance à **17 milliards en 2030**. En Australie, ce coût était de **19 milliards en 2016** et devrait atteindre **39 milliards en 2031**.

Ces défis ont motivé l'émergence d'une nouvelle génération de solutions numériques : les **systèmes de stationnement intelligent (Smart Parking Systems \- SPS)**. Ces systèmes exploitent des technologies telles que l'Internet des Objets (IoT), l'intelligence artificielle (IA), le machine learning, les capteurs intelligents et les systèmes cloud pour optimiser l'utilisation des espaces de stationnement et améliorer l'expérience utilisateur.

#### 1.Objectifs Stratégiques

Les systèmes de smart parking visent à **réduire le temps de recherche de stationnement** par la diminution du temps passé à chercher une place de 3-14 minutes vers quelques minutes seulement mais aussi par conséquent :

1. **Décongestioner le trafic urbain** : réduction de 30% du trafic inutile générée par la recherche de parking  
2. **Minimiser les émissions polluantes** : baisse des émissions CO₂ et des polluants atmosphériques  
3. **Optimiser l'utilisation de l'espace** : meilleure rentabilité des parkings existants, moins besoin de nouvelles infrastructures  
4. **Améliorer l'expérience utilisateur** : interface conviviale, réservation anticipée, paiement sans contact  
5. **Favoriser la mobilité durable** : intégration avec les transports publics et véhicules électriques

#### 2.Potentiel de Marché

Le marché global des systèmes de stationnement intelligent devrait connaître une **croissance annuelle de 18,5%** et atteindre **21 milliards de dollars d'ici 2030**. Cette croissance rapide reflète l'intérêt croissant des villes du monde entier et des investissements publics et privés substantiels dans ces solutions.

---

## COMPOSANTES TECHNOLOGIQUES PRINCIPALES

### Capteurs et Systèmes de Détection

**Capteurs distribués** : Ultrasons, magnétomètres, capteurs infrarouges (IR), boucles magnétiques placés à chaque place de parking pour détecter la présence de véhicules.  
**Systèmes de vision par ordinateur** : Caméras haute définition associées à des algorithmes de deep learning (CNN, YOLO) pour la détection d'occupation et la reconnaissance de plaques d'immatriculation.  
**Technologies de communication** : LoRaWAN, Wi-Fi, Bluetooth, 5G pour la transmission des données depuis les capteurs vers les nœuds de traitement.

### Architecture Informatique

**2 Modèles d'architectures possibles** :

Nous avons le **Cloud computing centralisé** qui passe par un traitement des données dans des datacenters distants et le **Fog/Edge computing** qui fonctionne via un traitement décentralisé à proximité des parkings pour réduire la latence

### Algorithmes et Intelligence Artificielle

- **Reconnaissance optique de caractères (OCR)** : identification automatique des plaques d'immatriculation  
- **Machine learning** : prédiction de la demande, allocation optimale des places  
- **Deep learning** : CNN, YOLO v8 pour la détection de véhicules et places libres  
- **Optimisation mathématique** : modèles MILP (Mixed Integer Linear Programming) pour allocation efficace

### Interfaces Utilisateurs

- **Applications mobiles** : consultation en temps réel, réservation de places, paiement  
- **Affichages numériques** : LED dynamiques guidant les conducteurs vers les places libres les plus proches  
- **Systèmes de guidage** : navigation intra-parking optimisée

*Illustration non reproduite ici (droits) — source : <https://pub.mdpi-res.com/sensors/sensors-20-01476/article_deploy/html/images/sensors-20-01476-g001.png>*

---

## ÉTAT DE L’ART ACTUEL

L’objectif principal de notre travail était de réaliser un état de l’art des recherches et articles scientifiques concernant le sujet suivant : “ Optimiser le stationnement pour une mobilité fluide et durable”.

### État Actuel et Maturité Technologique

Cette étude d'état de l'art couvre 26 articles scientifiques et techniques publiés entre 2012 et 2025, documentant l'évolution continue des systèmes de smart parking. Les résultats montrent une progression claire des technologies, passant des solutions simples basées sur capteurs (2012-2016) vers des systèmes sophistiqués intégrant IA, vision par ordinateur et architecture cloud-fog (2023-2025).

#### Tendances Majeures Identifiées

1. **Transition vers l'intelligence artificielle** : passage des capteurs passifs vers le deep learning et machine learning pour une meilleure détection et prédiction  
2. **Architecture distribuée** : adoption croissante du fog computing pour réduire la latence et les coûts de traitement centralisé  
3. **Support multilingue** : intégration de la reconnaissance de plaques en arabe et anglais pour adaptation régionale  
4. **Sécurité et confidentialité** : émergence des solutions blockchain et cryptographie quantique pour protéger les données des utilisateurs  
5. **Durabilité environnementale** : intégration de sources d'énergie renouvelables (panneaux solaires) et optimisation énergétique des dispositifs IoT  
6. **Mobilité autonome** : systèmes de parking robotisé pour parcs autonomes

### Défis Persistants

Malgré les avancées technologiques, plusieurs défis majeurs demeurent :

- **Coûts d'implémentation élevés** : infrastructure initiale coûteuse (capteurs, caméras, serveurs)  
- **Sécurité des données** : risques de piratage et nécessité de protéger la confidentialité des utilisateurs  
- **Conditions environnementales** : sensibilité aux variations d'éclairage, météo, obstruction visuelle  
- **Scalabilité** : difficulté à déployer à l'échelle d'une ville entière avec cohérence  
- **Interopérabilité** : manque de standards communs entre différents systèmes et fournisseurs  
- **Acceptation publique** : faible sensibilisation utilisateurs et résistance au changement  
- **Maintenance** : coûts opérationnels élevés, remplacement batteries capteurs

### Perspectives d'Avenir

Les systèmes de smart parking évoluent rapidement vers des solutions plus intelligentes, autonomes et durables. Les prochaines années verront probablement :

- **Intégration complète** avec les véhicules autonomes et les systèmes de mobilité multimodale  
- **IA avancée** permettant prédiction très précise et adaptation en temps réel  
- **Edge-AI** : intelligence embarquée dans les capteurs et appareils décentralisés  
- **Durabilité** : systèmes alimentés énergies renouvelables, zéro émission carbone  
- **Gouvernance smart** : optimisation globale transport, parking, énergie via IoT et big data

## CONCLUSION GÉNÉRALE

Le smart parking n'est plus une technologie futuriste, mais une **réalité opérationnelle** dans de nombreuses villes. Les systèmes modernes, combinant IoT, IA et architecture cloud-fog distribuée, offrent des **bénéfices tangibles** : réduction du temps de recherche, diminution du trafic et pollution, amélioration de l'expérience utilisateur, augmentation des revenus pour opérateurs.

Cependant, la réussite dépend de la capacité à surmonter les défis technologiques, économiques et sociaux. Une **approche intégrée**, combinant innovation technologique, gouvernance collaborative et durabilité environnementale, est essentielle pour transformer le stationnement urbain et contribuer à des villes plus intelligentes, efficaces et durables.

Le potentiel du marché (21 milliards USD en 2030\) et la croissance rapide (18,5% annuel) confirment que le smart parking restera un **domaine d'innovation majeur** pour la prochaine décennie, attirant investissements, talents et entrepreneuriat.

---

**État de l'art réalisé : décembre 2025** **Nombre d'articles analysés : 26** **Période couverte : 2012-2025** **Domaines couverts : IoT, IA, Vision par Ordinateur, Cloud/Fog Computing, Blockchain, Mobilité Urbaine**  
Récapitulatif des 26 Articles Trouvés et Analysés

---

Article 2 \- ScienceDirect 2023 : "A review of smart parking systems"

- **Année** : 2023  
- **Lien** : [https\://www\.sciencedirect.com/science/article/pii/S235214652301219X](https://www.sciencedirect.com/science/article/pii/S235214652301219X)  
- **Type** : Revue de littérature (124 études analysées)  
- **Analyse points faibles** :  
  - Coûts d'installation élevés (surtout caméras/VANET)  
  - Sécurité données et piratage signaux sans fil  
  - Dépendance conditions environnementales  
  - Faible acceptation publique

---

Article 6 \- PeerJ 2025 : "An Edge–Cloud Integrated Smart Parking Framework"

- **Année** : 2025  
- **Lien** : [https\://peerj.com/articles/cs-2544/](https://peerj.com/articles/cs-2544/)  
- **Type** : Article recherche (système complet IoT \+ ML)  
- **Technologies** : Vision ordinateur, OCR, YOLOv8, SVM, KNN  
- **Résultats** : Précision 97%  
- **Analyse points faibles** :  
  - Surcharge potentielle cloud  
  - Vulnérabilité échange données edge-cloud  
  - Défis standardisation protocoles

---

Article 7 \- Nature Scientific Reports 2025 : "A Vision-Based Smart Parking System Using Deep Learning"

- **Année** : 2025  
- **Lien** : [https\://www\.nature.com/articles/s41598-025-91565-0](https://www.nature.com/articles/s41598-025-91565-0)  
- **Type** : Article système CNN  
- **Technologie** : Réseaux neuronaux convolutifs CNN  
- **Avantages** : Évite capteurs physiques  
- **Analyse points faibles** :  
  - Sensibilité variations d'éclairage  
  - Conditions climatiques affectent performance  
  - Hardware GPU coûteux

---

Article 17 \- Nature 2025 : "Real time smart parking system based on IoT and fog computing"

- **Année** : 2025  
- **Lien** : [https\://www\.nature.com/articles/s41598-025-15507-6](https://www.nature.com/articles/s41598-025-15507-6)  
- **Type** : Déploiement réel (cas SDU University)  
- **Architecture** : 4 couches (edge/fog/proxy/cloud)  
- **Résultats** : Latence fog 14.65-367ms vs cloud 209-2213ms  
- **Analyse points faibles** :  
  - Simulation-based, pas implémentation réelle algorithmes  
  - Contexte universitaire non généralisable  
  - ML intégration future

---

Article 24 \- ScienceDirect 2023 : "Parking demand forecasting based on improved ICEEMDAN-GRU model"

- **Année** : 2023  
- **Type** : Modèle prédiction machine learning  
- **Technologie** : ICEEMDAN \+ GRU (Gated Recurrent Unit)  
- **Résultats** : 59.29% réduction RMSE, 64.08% diminution MAE  
- **Analyse points faibles** :  
  - Spécifique hub transport  
  - Nécessite données historiques extensives

---

ARTICLES REVUES ET ANALYSES (2023-2025)  
Article 7.5 \- 2025 : "Effective Smart parking systems: A review"

- **Année** : 2025 (Nile Journal of Communication & Computer Science)  
- **Lien** : [https\://njccs.journals.ekb.eg/article\_449715\_5656cf4735ef41a8d3dd31ac4b654b1a.pdf](https://njccs.journals.ekb.eg/article_449715_5656cf4735ef41a8d3dd31ac4b654b1a.pdf)  
- **Type** : Revue systématique complète  
- **Couverture** : WSN, VANET, MAS, image processing, 93 références  
- **Analyse points faibles** :  
  - VANET adoption limitée  
  - Image processing coûteux  
  - Scalabilité/interopérabilité

---

Article 20 \- 2024 : "Machine Learning-Based Prediction of Parking Space Availability"

- **Année** : 2024 (Wiley)  
- **Type** : Comparaison modèles ML  
- **Modèles** : Random Forest, KNN, DT, LR, Naïve Bayes  
- **Meilleur** : Random Forest  
- **Analyse points faibles** :  
  - Scalabilité  
  - Dépendance qualité données  
  - Privacy/sécurité

---

ARTICLES TECHNOLOGIES INNOVANTES (2022-2024)  
Article 21 \- 2022 : "Blockchain-enabled Secure Framework for Energy-Efficient Smart Parking"

- **Type** : Blockchain \+ Deep LSTM  
- **Architecture** : 6 couches (RSU-based, ECC, virtualization)  
- **Points forts** : Sécurité, energy-efficient  
- **Points faibles** : Complexité, scalabilité, adoption limitée

---

Article 23 \- 2025 : "Efficiency of a smart parking system in privacy-preserving consortium blockchain"

- **Type** : Quantum Blind Signature \+ Blockchain  
- **Innovation** : Cryptographie quantique  
- **Points forts** : Privacy préservation  
- **Points faibles** : Complexité, latency blockchain

---

Article 22 \- 2024 : "Predicting University Campus Parking Demand Using Machine Learning Models"

- **Type** : Campus universitaire (PANN, EANN)  
- **Données** : Patterns académiques  
- **Résultats** : PANN R² \= 0.846 vs linéaire 0.431

---

ARTICLES HARDWARE/PROTOTYPES (2019-2023)  
Article 25 \- 2023 : "Provenance-based smart parking system with multilevel fog nodes"

- **Conférence** : IEEE APCC 2023 (Sydney)  
- **Type** : Système fog computing multi-niveaux  
- **Innovation** : Traçabilité données (provenance)

---

Article 26 \- 2023 : "Low-cost, High Accuracy Smart Parking Solution"

- **Type** : SPU (Smart Parking Unit)  
- **Capteur** : Magnétomètre  
- **Connectivité** : LPWA  
- **Avantage** : Coût bas

---

Article 19 \- 2024 : "Cloud Driven Smart Car Parking System"

- **Année** : 2024  
- **Type** : Système cloud intégré IoT  
- **Outils** : VS Code, Figma, React JS, AWS  
- **Déploiement** : Pilote avec résultats positifs

---

ARTICLES PROTOTYPES ÉDUCATIFS (2019-2022)  
Article 8 \- 2020 : "Conception et réalisation d'un système de parking intelligent"

- **Type** : Mémoire universitaire  
- **Technologie** : Arduino \+ capteurs ultrasons  
- **Points faibles** : Petite échelle, peu évolutif

---

Article 9 \- 2021 : "Développement d'un système de stationnement intelligent"

- **Type** : Mémoire universitaire  
- **Technologie** : Arduino \+ capteurs \+ app Bluetooth  
- **Points faibles** : Bluetooth portée limitée, pas scalable

---

Article 10 \- 2022 : "Smart Parking, Smart City, Arduino UNO, Mobile App"

- **Type** : Mémoire universitaire  
- **Technologie** : Arduino UNO \+ app mobile  
- **Points faibles** : Pas cloud, architecture simple

---

Article 11 \- 2020 : "Application à la conception d'un parking intelligent"

- **Type** : Mémoire universitaire  
- **Technologie** : Capteurs IR \+ communication série  
- **Points faibles** : Série non adaptée, pas interface

---

Article 12 \- 2019 : "REALISATION D'UN SYSTEME DE STATIONNEMENT"

- **Type** : Mémoire universitaire  
- **Technologie** : LED locales  
- **Points faibles** : Système local, zéro connectivité IoT

---

ARTICLES FONDAMENTAUX (2012-2018)  
Article 1 \- 2016 : "Car Park System: A Review of Smart Parking"

- **Type** : Revue synthétique  
- **Structure** : 4 composantes (PGIS, paiement, e-parking, transit)  
- **Points faibles** : Conceptuel, données limitées, pas exemples réels

---

Article 3 \- 2023 : "Smart Cities—A Structured Literature Review"

- **Type** : Revue 83 publications  
- **Scope** : Smart cities globales (pas focus parking)  
- **Points faibles** : Générale, pas détail technique parking

---

Article 4 \- 2016 : "Internet of Things Approach to Cloud-Based Smart Car Parking"

- **Type** : Architecture IoT-VANET-Cloud  
- **Innovation** : Communication inter-véhiculaire  
- **Points faibles** : Coûts VANET, complexité réseau

---

Article 5 \- 2012 : "A new Smart Parking System Infrastructure and Implementation"

- **Type** : Architecture MILP optimisation  
- **Technologie** : Capteurs \+ LEDs \+ réservation  
- **Innovation** : Pionnière optimisation algorithmique  
- **Points faibles** : Coûts élevés, maintenance

---

Article 13 \- 2023 : "Etat de L'art D'un Smart Parking, Étude Et Conception"

- **Type** : Document générale technologies  
- **Utilité** : Point d'entrée panorama  
- **Points faibles** : Descriptif, pas comparative

---

Article 14 \- 2018 : "Smart Parking: Stationnement intelligent État de l'art"

- **Format** : Présentation SlideShare  
- **Type** : Vulgarisation concepts  
- **Points faibles** : Non académique, pas rigueur

---

Article 18 \- 2018 : "Real-time image-based parking occupancy detection using deep CNN"

- **Type** : Étude CNN \+ SVM  
- **Technologie** : Transfer learning  
- **Dataset** : PKLot publique  
- **Résultat** : \>95% accuracy

---

RESSOURCES ADDITIONNELLES  
Outils de recherche recommandés :

- Google Scholar: [https\://scholar.google.com/](https://scholar.google.com/)  
- ScienceDirect: [https\://www\.sciencedirect.com/](https://www.sciencedirect.com/)  
- IEEE Xplore: [https\://ieeexplore.ieee.org/](https://ieeexplore.ieee.org/)  
- arXiv: [https\://arxiv.org/](https://arxiv.org/)  
- ResearchGate: [https\://www\.researchgate.net/](https://www.researchgate.net/)

Mots-clés efficaces :

- "smart parking" OR "intelligent parking"  
- "parking occupancy detection"  
- "parking demand prediction"  
- "IoT parking management"  
- "license plate recognition ANPR"  
- "parking guidance system PGIS"  
- "autonomous parking"  
- "smart city parking"

**Dernière mise à jour : Décembre 2025** **Total articles documentés : 26** **Période couverte : 2012-2025**
