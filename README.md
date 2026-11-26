# SmartParking

Prototype de parking intelligent à bas coût, réalisé à l'ESTP Paris dans le module *Initiation à la recherche* (année 2025-2026).

Chaque place est équipée d'un capteur à ultrasons et d'un voyant. Le parking calcule lui-même ses places libres (edge computing) et les publie en MQTT. Les parkings d'une même ville s'écoutent entre eux : quand l'un est plein, il redirige le conducteur vers un autre qui a de la place. Un tableau de bord web affiche l'état en direct.

## Démarche

1. **État de l'art** (décembre 2025) : 26 articles scientifiques et techniques analysés, de 2012 à 2025. Il compare les capteurs distribués (ultrasons, magnétomètres, infrarouge) et la vision par ordinateur (caméras et deep learning : CNN, YOLOv8), ainsi que les architectures cloud et edge/fog.
   → [`docs/etat-de-l-art.md`](docs/etat-de-l-art.md) et le tableau détaillé [`docs/bibliographie-26-articles.csv`](docs/bibliographie-26-articles.csv)
2. **Choix technique** : capteurs à ultrasons HC-SR04 plutôt que caméras et IA. Ce choix réduit le coût et la consommation, et ne pose pas de question de vie privée. Le traitement est fait sur place, et seul le nombre de places libres circule sur le réseau.
3. **Prototype**, en deux versions simulées sous [Wokwi](https://wokwi.com) :
   - un parking de 10 places sur Arduino Mega, avec écran LCD et bouton d'entrée ;
   - un parking de 4 places sur ESP32, connecté en Wi-Fi et MQTT, avec routage entre plusieurs parkings.
4. **Rapport final** : [`docs/rapport-final.pdf`](docs/rapport-final.pdf)

## Architecture (version ESP32)

```
Capteurs HC-SR04 ─▶ ESP32 (état des places, réservation, routage) ─▶ broker MQTT ─▶ tableau de bord web
    + voyants         écran LCD 20x4, bouton « barrière »            topic smartcity_demo_2026/<parking>/etat
```

- Une place passe par trois états : **libre** (vert), **réservée** (orange) ou **occupée** (rouge). Une réservation qui n'est pas confirmée au bout de 5 s est libérée.
- Chaque parking publie `{"id": "P1", "libres": n}` et s'abonne aux messages des autres parkings de la ville.

## Contenu du dépôt

| Chemin | Rôle |
|---|---|
| `src/main.cpp` | Firmware ESP32 (PlatformIO) |
| `platformio.ini` | Configuration PlatformIO (ESP32, LiquidCrystal_I2C, PubSubClient, ArduinoJson) |
| `diagram.json`, `wokwi.toml` | Circuit et simulation Wokwi de la version ESP32 |
| `arduino-mega/` | Version 10 places sur Arduino Mega : code et circuit Wokwi |
| `dashboard/index.html` | Tableau de bord web temps réel (MQTT par WebSocket) |
| `docs/` | État de l'art, bibliographie, rapport final |

## Lancer la simulation

1. Compiler avec PlatformIO : `pio run`.
2. Lancer la simulation avec l'extension Wokwi pour VS Code, qui lit `wokwi.toml` et `diagram.json`.
3. Ouvrir `dashboard/index.html` dans un navigateur pour suivre l'état en direct.

Pour simuler plusieurs parkings, changer `ID_PARKING` (P1, P2, P3) dans `src/main.cpp` et lancer une simulation par parking.

Le prototype utilise le broker public `broker.hivemq.com` : c'est pratique pour une démonstration, mais il ne convient pas à un usage réel.

## Équipe

Nalan Tagore, Eric Grandsart, Moussa Nassour, Allonzo Pensabene — ESTP Paris.
