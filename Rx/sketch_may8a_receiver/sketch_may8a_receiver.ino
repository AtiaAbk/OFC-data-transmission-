#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorPin = 7;

int count = 0;
bool lastState = HIGH;

unsigned long lastPulseTime = 0;

bool locked = false;

void setup() {

  pinMode(sensorPin, INPUT);

  lcd.begin(16, 2);

  lcd.setCursor(4, 0);
  lcd.print("K.S.A");

  lcd.setCursor(2, 1);
  lcd.print("OFC SYSTEM");

  delay(2000);
  lcd.clear();
}

void loop() {

  bool state = digitalRead(sensorPin);


  if (!locked && lastState == HIGH && state == LOW) {

    count++;
    locked = true;              // lock same pulse
    lastPulseTime = millis();
  }

  // unlock after pulse ends
  if (state == HIGH) {
    locked = false;
  }

  lastState = state;

  // transmission end detect
  if (count > 0 && millis() - lastPulseTime > 2000) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Received:");

    lcd.setCursor(0, 1);
    lcd.print(count);

    delay(3000);

    count = 0;
    lcd.clear();
  }
}
