#include <LiquidCrystal.h>

// LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorPin = 7;

void setup() {

  pinMode(sensorPin, INPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("OFC RX Module");
}

void loop() {

  int sensorState = digitalRead(sensorPin);

  lcd.setCursor(0, 1);

  // Light detected
  if (sensorState == LOW) {

    lcd.print("Signal Received");

  }

  // No light
  else {

    lcd.print("No Signal      ");
  }

  delay(100);
}