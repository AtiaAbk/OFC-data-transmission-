#include <LiquidCrystal.h>

// LCD pin order: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int ledPin = 8;

// Track animation timing and UI state
unsigned long lastAnimation = 0;
const unsigned long ANIM_INTERVAL = 300000UL; // 5 minutes
bool uiDrawn = false;

void runStartupAnimation();
void showMainUI();

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  runStartupAnimation();
  lastAnimation = millis();
}

void runStartupAnimation() {
  lcd.clear();

  // Step 1: Scroll K.S.A label across row 1
  for (int i = 0; i < 3; i++) {
    lcd.setCursor(0, 0);
    lcd.print("Initializing...");
    lcd.setCursor(i * 2, 1);
    lcd.print("K.S.A");
    delay(700);
    lcd.clear();
  }

  // Step 2: Centered branding splash
  lcd.setCursor(5, 0);
  lcd.print("K.S.A");
  lcd.setCursor(3, 1);
  lcd.print("OFC SYSTEM");
  delay(2000);
  lcd.clear();
}

void showMainUI() {
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("OFC TX Module");
  lcd.setCursor(0, 1);
  lcd.print("Enter num (1-9):");
}

void loop() {

  // Replay animation every 5 minutes
  if (millis() - lastAnimation >= ANIM_INTERVAL) {
    runStartupAnimation();
    lastAnimation = millis();
    uiDrawn = false;
  }

  // Draw main UI once, not on every loop tick
  if (!uiDrawn) {
    showMainUI();
    uiDrawn = true;
  }

  if (Serial.available() > 0) {
    int number = Serial.parseInt();

    if (number >= 1 && number <= 9) {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sending...");
      lcd.setCursor(0, 1);
      lcd.print(number);
      delay(1500);

      // Transmit pulses via LED
      for (int i = 0; i < number; i++) {
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(800);
      }

      // Success screen
      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("DONE!");
      lcd.setCursor(0, 1);
      lcd.print("Sent: ");
      lcd.print(number);
      lcd.print(" pulse(s)");
      delay(3500);

      uiDrawn = false;
    }
  }
}