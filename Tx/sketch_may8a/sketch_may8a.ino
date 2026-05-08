#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int ledPin = 8;

unsigned long lastAnimation = 0;
const unsigned long interval = 300000; // 5 minutes

void setup() {

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  lcd.begin(16, 2);

  runStartupAnimation();
}

void runStartupAnimation() {

  lcd.clear();

  // Step 1: Scroll "K.S.A"
  for (int i = 0; i < 3; i++) {

    lcd.setCursor(0, 0);
    lcd.print("Initializing");

    lcd.setCursor(i * 2, 1);
    lcd.print("K.S.A");

    delay(700);
    lcd.clear();
  }

  // Step 2: Final branding
  lcd.setCursor(5, 0);
  lcd.print("K.S.A");

  lcd.setCursor(2, 1);
  lcd.print("OFC SYSTEM");

  delay(2000);

  lcd.clear();
}

void showMainUI() {

  lcd.setCursor(0, 0);
  lcd.print("Enter Number:");

  lcd.setCursor(0, 1);
  lcd.print("Ready TX Module");
}

void loop() {

  // 5-minute animation repeat
  if (millis() - lastAnimation >= interval) {

    runStartupAnimation();
    lastAnimation = millis();
  }

  showMainUI();

  if (Serial.available() > 0) {

    int number = Serial.parseInt();

    if (number > 0 && number <= 9) {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sending...");

      delay(500);

      for (int i = 0; i < number; i++) {

        digitalWrite(ledPin, HIGH);
        delay(300);

        digitalWrite(ledPin, LOW);
        delay(300);
      }

      lcd.clear();
      lcd.setCursor(4, 0);
      lcd.print("DONE");
      lcd.setCursor(0, 1);
      lcd.print("Sent Successfully");

      delay(2000);

      lcd.clear();
    }
  }
}