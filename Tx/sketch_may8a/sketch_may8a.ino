#include <LiquidCrystal.h>

// LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int ledPin = 8;

void setup() {

  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("OFC TX Module");

  lcd.setCursor(0, 1);
  lcd.print("Enter Number");
}

void loop() {

  // Check serial input
  if (Serial.available() > 0) {

    int number = Serial.parseInt();

    // Valid number check
    if (number > 0 && number <= 9) {

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Sending:");

      lcd.setCursor(0, 1);
      lcd.print(number);

      delay(1000);

      // Send pulses
      for (int i = 0; i < number; i++) {

        digitalWrite(ledPin, HIGH);
        delay(500);

        digitalWrite(ledPin, LOW);
        delay(500);
      }

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Done Sending");

      delay(1500);

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Enter Number");
    }
  }
}