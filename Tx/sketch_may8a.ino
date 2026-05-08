#include <LiquidCrystal.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int buttonPin = 7;   // Push button
int ledPin = 8;      // LED (light source)

void setup() {

  // Button uses internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // LED output
  pinMode(ledPin, OUTPUT);

  // LCD start
  lcd.begin(16, 2);

  // First line
  lcd.setCursor(0, 0);
  lcd.print("OFC TX Module");
}

void loop() {

  // Button pressed
  if (digitalRead(buttonPin) == LOW) {

    // LED ON
    digitalWrite(ledPin, HIGH);

    // LCD message
    lcd.setCursor(0, 1);
    lcd.print("Signal Sent   ");
  }

  // Button not pressed
  else {

    // LED OFF
    digitalWrite(ledPin, LOW);

    // LCD message
    lcd.setCursor(0, 1);
    lcd.print("Waiting...    ");
  }
}