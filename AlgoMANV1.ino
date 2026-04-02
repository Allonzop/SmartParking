#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Configuration
const int seuil = 50;
const unsigned long tempsTrajet = 2000; // 2 secondes de simulation
const int pinBouton = 44;

// États possibles pour une place
enum EtatPlace { LIBRE, RESERVEE, OCCUPEE };
EtatPlace etats[10] = {LIBRE};
unsigned long timerReservation[10] = {0};

// Pins
int trigPin[10] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40};
int echoPin[10] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41};
int ledRouge[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 42};
int ledVert[10]  = {3, 5, 7, 9, 11, 13, 15, 17, 19, 43};

// Variables pour le bouton
bool dernierEtatBouton = HIGH;
unsigned long tempsDernierMessage = 0;
int placeAffichee = -1;

void setup() {
  pinMode(pinBouton, INPUT_PULLUP);
  for(int i = 0; i < 10; i++){
    pinMode(trigPin[i], OUTPUT); 
    pinMode(echoPin[i], INPUT);  
    pinMode(ledRouge[i], OUTPUT);  
    pinMode(ledVert[i], OUTPUT);
  } 
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  
  lcd.setCursor(4, 1);
  lcd.print("SYSTEME PRET");
  delay(1500);
  lcd.clear();
}

long lireDistance(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duree = pulseIn(echo, HIGH, 20000);
  if (duree == 0) return 999; // Si pas d'echo, on considère libre
  return (duree * 0.034) / 2;
}

void loop() {
  int libresA = 0;
  int libresB = 0;
  unsigned long maintenant = millis();

  // 1. GESTION DES CAPTEURS ET DES ÉTATS
  for(int i = 0; i < 10; i++){
    long d = lireDistance(trigPin[i], echoPin[i]);
    bool presencePhysique = (d < seuil);

    // Si le capteur détecte quelqu'un -> Occupé d'office
    if(presencePhysique) {
      etats[i] = OCCUPEE;
    } 
    // Si c'était réservé, on vérifie si le temps de trajet est fini
    else if (etats[i] == RESERVEE) {
      if (maintenant - timerReservation[i] > tempsTrajet) {
        // Le temps est fini, si tjs pas de voiture détectée, elle redevient libre (ou reste en attente)
        // Ici on la remet LIBRE pour permettre une nouvelle attribution si la voiture a disparu
        etats[i] = LIBRE;
      }
    } 
    else {
      etats[i] = LIBRE;
    }

    // Gestion des LEDs
    if(etats[i] == LIBRE) {
      digitalWrite(ledVert[i], HIGH); digitalWrite(ledRouge[i], LOW);
      if(i < 5) libresA++; else libresB++;
    } 
    else if(etats[i] == RESERVEE) {
      // La LED clignote ou reste orange (ici Rouge+Vert pour simuler orange ou juste rouge)
      digitalWrite(ledVert[i], LOW); digitalWrite(ledRouge[i], HIGH); 
    } 
    else { // OCCUPEE
      digitalWrite(ledVert[i], LOW); digitalWrite(ledRouge[i], HIGH);
    }
  }

  // 2. GESTION DU BOUTON D'ENTRÉE (INTELLIGENCE)
  bool etatActuelBouton = digitalRead(pinBouton);
  if (dernierEtatBouton == HIGH && etatActuelBouton == LOW) {
    // On cherche une place libre
    int placeTrouvee = -1;
    for(int i=0; i<10; i++) {
      if(etats[i] == LIBRE) {
        placeTrouvee = i;
        break; 
      }
    }

    if(placeTrouvee != -1) {
      etats[placeTrouvee] = RESERVEE;
      timerReservation[placeTrouvee] = maintenant;
      placeAffichee = placeTrouvee + 1;
      tempsDernierMessage = maintenant;
      Serial.print("Voiture assignée à la place : "); Serial.println(placeAffichee);
    } else {
      placeAffichee = 0; // Code pour Parking Plein
      tempsDernierMessage = maintenant;
    }
    delay(200); // Debounce
  }
  dernierEtatBouton = etatActuelBouton;

  // 3. AFFICHAGE LCD
  // Lignes de stats fixes
  lcd.setCursor(0, 0);
  lcd.print("Zone A: "); lcd.print(libresA); lcd.print(" libres  ");
  
  lcd.setCursor(0, 1);
  lcd.print("Zone B: "); lcd.print(libresB); lcd.print(" libres  ");

  // Ligne d'intelligence (Message temporaire)
  lcd.setCursor(0, 3);
  if (maintenant - tempsDernierMessage < 3000) { // Affiche le message pendant 3s
    if(placeAffichee > 0) {
      lcd.print("ALLEZ EN PLACE P"); lcd.print(placeAffichee);
      lcd.print("   "); // Les espaces nettoient la fin de ligne
    } else if (placeAffichee == 0) {
      lcd.print("!! PARKING PLEIN !! "); // Pile 20 caractères
    }
  } else {
    // Raccourci pour ne pas dépasser 20 caractères au total !
    lcd.print("TOTAL LIBRES : "); 
    lcd.print(libresA + libresB);
    lcd.print("    "); // Nettoie les anciens caractères
  }
}