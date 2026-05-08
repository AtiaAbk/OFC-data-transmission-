#include <LiquidCrystal.h>

// LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// LDR Module DO pin
int sensorPin = 7;

int pulseCount = 0;
bool previousState = HIGH;

unsigned long lastPulseTime = 0;

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

  // Detect pulse
  if (previousState == HIGH && currentState == LOW) {

    pulseCount++;

    lastPulseTime = millis();

    delay(50);
  }

  previousState = currentState;

  // If transmission finished
  if (pulseCount > 0 && millis() - lastPulseTime > 1500) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Received:");

    lcd.setCursor(0, 1);
    lcd.print(pulseCount);

    delay(3000);

    // Reset
    pulseCount = 0;

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Waiting...");
  }
}