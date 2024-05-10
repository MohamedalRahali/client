

// Déclaration de la broche à laquelle la LED est connectée
const int pinLED = 12;

void setup() {
  // Configuration de la broche de la LED en sortie
  pinMode(pinLED, OUTPUT);
}

void loop() {
  // Allumer la LED en mettant la broche à l'état HIGH
  digitalWrite(pinLED, HIGH);
  // Attendre une seconde
  delay(1000);
  // Éteindre la LED en mettant la broche à l'état LOW
  digitalWrite(pinLED, LOW);
  // Attendre une seconde
  delay(1000);
}
