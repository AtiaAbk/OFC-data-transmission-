#include <LiquidCrystal.h>

// LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorPin = 7;

int pulseCount = 0;

bool lastState = HIGH;

unsigned long lastDetectTime = 0;

void setup() {

  pinMode(sensorPin, INPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("OFC RX Module");

  lcd.setCursor(0, 1);
  lcd.print("Waiting...");
}

void loop() {

  bool currentState = digitalRead(sensorPin);

  // Detect only one falling edge
  if (lastState == HIGH && currentState == LOW) {

    pulseCount++;

    lastDetectTime = millis();

    // Wait so same pulse is not counted again
    delay(300);
  }

  lastState = currentState;

  // Transmission finished
  if (pulseCount > 0 && millis() - lastDetectTime > 2000) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Received:");

    lcd.setCursor(0, 1);
    lcd.print(pulseCount);

    delay(3000);

    pulseCount = 0;

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Waiting...");
  }
}