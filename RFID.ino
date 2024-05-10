#include <LiquidCrystal_I2C.h> 
#define BUZZER_PIN  8
#define LED_PIN  4

int etat = 1;
String valeurentrer = "";

String info;
LiquidCrystal_I2C lcd(0x27, 20, 4);


void setup() {
  Serial.begin(9600); 
  lcd.init(); // Initialisation de l'afficheur
  lcd.clear();
  lcd.backlight(); // Activer le rétroéclairage
  lcd.setCursor(0, 0); // Se positionner à la première ligne
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  lcd.print("bienvenue ");
}

String readnumber() {
  String message = "";
  while (message == "") {
    while (!Serial.available());
    message = Serial.readString();
  }
  return message;
}

void affiche2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(info);
}

void loop() {
  while (etat == 1) {
    lcd.setCursor(0, 0);
    lcd.print("bienvenue ");
    lcd.setCursor(0, 1);
    lcd.print(valeurentrer); 
    Serial.println(valeurentrer);
    if (info != "Not found") {
      digitalWrite(LED_PIN, HIGH); 
      delay(500);
      digitalWrite(LED_PIN, LOW);
    }
    etat = 2;
  }
  
  while (etat == 2) {
    info = readnumber();
    affiche2();
    if (info == "Not found") {
      tone(BUZZER_PIN, 1000);
      delay(500);
      etat=1;
    }
    
  }
}
