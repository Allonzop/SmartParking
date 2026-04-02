#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialisation de l'écran LCD I2C (Adresse 0x27, 20 colonnes, 4 lignes)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Seuil de détection en cm
const int seuil = 50;

// ---------------- MAPPAGE DES BROCHES ----------------
// Capteurs HC-SR04 (10 places)
int trigPin[10] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40};
int echoPin[10] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41};

// LEDs Rouges et Vertes (10 places)
int ledRouge[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 42};
int ledVert[10]  = {3, 5, 7, 9, 11, 13, 15, 17, 19, 43};

// Tableau des états (false = libre, true = occupé)
bool etat[10] = {false, false, false, false, false, false, false, false, false, false};

void setup() {
  for(int i = 0; i < 10; i++){
    pinMode(trigPin[i], OUTPUT); 
    pinMode(echoPin[i], INPUT);  
    pinMode(ledRouge[i], OUTPUT);  
    pinMode(ledVert[i], OUTPUT);
  } 
  
  lcd.init();        // Initialisation de l’écran LCD
  lcd.backlight();   // Active le rétroéclairage
  Serial.begin(9600); 

  // Affichage du message de bienvenue centré sur un 20x4
  lcd.setCursor(3, 1);
  lcd.print("SMART PARKING");
  lcd.setCursor(4, 2);
  lcd.print("10 PLACES");
  delay(2000);
  lcd.clear();
}

long lireDistance(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);  // Impulsion de 10µs standard pour le HC-SR04
  digitalWrite(trig, LOW);
  
  long duree = pulseIn(echo, HIGH, 20000); 
  
  // Vitesse du son : 340 m/s soit 0.034 cm/µs
  return (duree * 0.034) / 2; 
}

void loop() {
  int libresZoneA = 0; // Places 1 à 5 (Index 0 à 4)
  int libresZoneB = 0; // Places 6 à 10 (Index 5 à 9)
  
  for(int i = 0; i < 10; i++){
    long d = lireDistance(trigPin[i], echoPin[i]);
    
    // Debug série
    Serial.print("Place "); Serial.print(i + 1);
    Serial.print(" = "); Serial.print(d); Serial.println(" cm");

    // Gestion des LEDs et de l'état
    if(d > 0 && d < seuil){ // Occupé (d>0 évite les faux positifs si le capteur ne lit rien)
      digitalWrite(ledRouge[i], HIGH);                   
      digitalWrite(ledVert[i], LOW);                   
      etat[i] = true;                                       
    } else { // Libre
      digitalWrite(ledRouge[i], LOW);                   
      digitalWrite(ledVert[i], HIGH);
      etat[i] = false;
    }

    // Comptage des places par zone
    if(i < 5 && !etat[i]) libresZoneA++;
    if(i >= 5 && !etat[i]) libresZoneB++;
    
    delay(50); // Pause courte pour éviter les échos croisés entre capteurs
  }

  // Affichage LCD
  lcd.setCursor(0, 0);
  lcd.print("Zone A libres: "); 
  lcd.print(libresZoneA);
  lcd.print(" "); // Efface le caractère précédent si on passe de 10 à 9

  lcd.setCursor(0, 1);
  lcd.print("Zone B libres: "); 
  lcd.print(libresZoneB);
  lcd.print(" ");

  lcd.setCursor(0, 3);
  lcd.print("Total libres : ");
  lcd.print(libresZoneA + libresZoneB);
  lcd.print("  ");

  Serial.println("-------------------");
  delay(500);
}