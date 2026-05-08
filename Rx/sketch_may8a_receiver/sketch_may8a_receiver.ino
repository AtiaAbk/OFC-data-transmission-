#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int ledPin = 8;

unsigned long animTimer = 0;
bool blinkState = false;

void startupScreen() {

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("K.S.A OFC");

  lcd.setCursor(4, 1);
  lcd.print("SYSTEM");

  delay(3000);
  lcd.clear();
}

void loadingAnimation() {

  static int i = 0;

  lcd.setCursor(0, 1);

  char anim[16];

  for (int j = 0; j < 16; j++) {
    anim[j] = (j <= i) ? '#' : ' ';
  }

  anim[15] = '\0';

  lcd.print(anim);

  i++;

  if (i > 15) i = 0;
}

void setup() {

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  lcd.begin(16, 2);

  startupScreen();
}

void loop() {

  lcd.setCursor(0, 0);
  lcd.print("Enter Number:");

  if (Serial.available() > 0) {

    int number = Serial.parseInt();

    if (number >= 1 && number <= 1000) {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sending...");
      
      delay(500);

      // Send pulses + loading animation
      for (int i = 0; i < number; i++) {

        digitalWrite(ledPin, HIGH);
        delay(100);
        digitalWrite(ledPin, LOW);
        delay(100);

        loadingAnimation();
      }

      // Success message
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Transmitted");
      lcd.setCursor(0, 1);
      lcd.print("Successfully");

      // Blink for 3 seconds 
      for (int i = 0; i < 6; i++) {

        lcd.noDisplay();
        delay(250);
        lcd.display();
        delay(250);
      }

      lcd.clear();
    }
  }
}