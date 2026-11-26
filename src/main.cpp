#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PubSubClient.h>
#include <ArduinoJson.h> 

// --- CONFIGURATION DU PARKING ---
#define ID_PARKING "P1" // À CHANGER POUR P2 ou P3 DANS LES AUTRES SIMULATIONS
const char* nom_ville = "smartcity_demo_2026"; 

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
LiquidCrystal_I2C lcd(0x27, 20, 4);

// --- HARDWARE ---
// --- HARDWARE ---
const int NB_PLACES = 4;
int trigPins[4]  = {5, 18, 19, 23};
int echoPins[4]  = {34, 35, 32, 15}; // <-- Pin 39 remplacé par 15
int ledRouges[4] = {13, 27, 25, 2};
int ledVertes[4] = {14, 26, 33, 4};  // <-- On utilise 33 et 4 pour que ce soit propre
const int PIN_BOUTON = 12; // Bouton de la barrière

// --- LOGIQUE ---
enum EtatPlace { LIBRE, RESERVEE, OCCUPEE };
EtatPlace etats[NB_PLACES] = {LIBRE, LIBRE, LIBRE, LIBRE};
unsigned long timerReservation[NB_PLACES] = {0};
const unsigned long DELAI_DOUTE = 5000; // 5 secondes
const int SEUIL_DETECTION = 50;

// Mémoire du réseau (pour rediriger)
int placesLibresP1 = 4, placesLibresP2 = 4, placesLibresP3 = 4;
unsigned long dernierEnvoi = 0;
bool dernierEtatBouton = HIGH;

// --- FONCTIONS ---
long lireDistance(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duree = pulseIn(echo, HIGH, 30000); 
  return (duree == 0) ? 400 : (duree * 0.034) / 2;
}

// Fonction qui écoute les autres parkings
void callbackMQTT(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) message += (char)payload[i];
  
  StaticJsonDocument<256> doc;
  deserializeJson(doc, message);
  
  String id = doc["id"];
  int libres = doc["libres"];
  
  if (id == "P1") placesLibresP1 = libres;
  else if (id == "P2") placesLibresP2 = libres;
  else if (id == "P3") placesLibresP3 = libres;
}

void reconnect() {
  while (!client.connected()) {
    String clientId = "Parking-" + String(ID_PARKING) + "-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      // S'abonne aux annonces de toute la ville
      String topicEcoute = String(nom_ville) + "/+/etat";
      client.subscribe(topicEcoute.c_str());
    } else {
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_BOUTON, INPUT_PULLUP);
  
  for(int i=0; i<NB_PLACES; i++) {
    pinMode(trigPins[i], OUTPUT); pinMode(echoPins[i], INPUT);
    pinMode(ledRouges[i], OUTPUT); pinMode(ledVertes[i], OUTPUT);
  }

  Wire.begin(21, 22); 
  lcd.init(); lcd.backlight();
  lcd.print("Demarrage "); lcd.print(ID_PARKING);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callbackMQTT);
  
  lcd.clear(); lcd.print("Reseau Ville OK!");
  delay(1000); lcd.clear();
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  int mesPlacesLibres = 0;
  unsigned long maintenant = millis();

  // 1. LECTURE DES CAPTEURS & GESTION DES 5 SECONDES
  for (int i = 0; i < NB_PLACES; i++) {
    long distance = lireDistance(trigPins[i], echoPins[i]);
    bool detectionForte = (distance < SEUIL_DETECTION);

    if (detectionForte) {
      etats[i] = OCCUPEE;
    } else {
      if (etats[i] == RESERVEE) {
        if (maintenant - timerReservation[i] > DELAI_DOUTE) {
          etats[i] = LIBRE; // La voiture n'est jamais arrivée
        }
      } else {
        etats[i] = LIBRE;
      }
    }

    // Affichage LEDs
    if (etats[i] == LIBRE) {
      digitalWrite(ledRouges[i], LOW); digitalWrite(ledVertes[i], HIGH);
      mesPlacesLibres++;
    } else if (etats[i] == RESERVEE) {
      digitalWrite(ledRouges[i], HIGH); digitalWrite(ledVertes[i], HIGH); // Fait un Orange/Jaune
    } else {
      digitalWrite(ledRouges[i], HIGH); digitalWrite(ledVertes[i], LOW);
    }
    delay(10);
  }

  // 2. BOUTON BARRIÈRE (Logique de routage)
  bool etatBouton = digitalRead(PIN_BOUTON);
  if (dernierEtatBouton == HIGH && etatBouton == LOW) {
    lcd.clear();
    
    // Cherche une place libre chez soi
    int placeTrouvee = -1;
    for(int i=0; i<NB_PLACES; i++) {
      if(etats[i] == LIBRE) { placeTrouvee = i; break; }
    }

    if (placeTrouvee != -1) {
      etats[placeTrouvee] = RESERVEE;
      timerReservation[placeTrouvee] = maintenant;
      lcd.setCursor(0,0); lcd.print("BIENVENUE");
      lcd.setCursor(0,1); lcd.print("Allez en place "); lcd.print(placeTrouvee + 1);
    } else {
      // Routage Intelligent
      lcd.setCursor(0,0); lcd.print("PARKING PLEIN");
      lcd.setCursor(0,1);
      
      if (String(ID_PARKING) != "P1" && placesLibresP1 > 0) lcd.print("-> Allez au P1");
      else if (String(ID_PARKING) != "P2" && placesLibresP2 > 0) lcd.print("-> Allez au P2");
      else if (String(ID_PARKING) != "P3" && placesLibresP3 > 0) lcd.print("-> Allez au P3");
      else lcd.print("VILLE COMPLETE !");
    }
    delay(3000); // Laisse le message 3s
    lcd.clear();
  }
  dernierEtatBouton = etatBouton;

  // 3. AFFICHAGE STANDARD
  lcd.setCursor(0, 0); lcd.print(ID_PARKING); lcd.print(" Libres: "); lcd.print(mesPlacesLibres);
  lcd.setCursor(0, 1); lcd.print("P1:"); lcd.print(placesLibresP1); lcd.print(" P2:"); lcd.print(placesLibresP2); lcd.print(" P3:"); lcd.print(placesLibresP3);

  // 4. PUBLICATION MQTT
  if (maintenant - dernierEnvoi > 2000) {
    StaticJsonDocument<256> doc;
    doc["id"] = ID_PARKING;
    doc["libres"] = mesPlacesLibres;
    JsonArray placesArr = doc.createNestedArray("places");
    
    for(int i=0; i<NB_PLACES; i++) {
      JsonObject p = placesArr.createNestedObject();
      p["id"] = i+1;
      if (etats[i] == LIBRE) p["etat"] = "LIB";
      else if (etats[i] == RESERVEE) p["etat"] = "RES";
      else p["etat"] = "OCC";
    }

    String payload;
    serializeJson(doc, payload);
    String topicPublish = String(nom_ville) + "/" + String(ID_PARKING) + "/etat";
    client.publish(topicPublish.c_str(), payload.c_str());
    dernierEnvoi = maintenant;
  }
}