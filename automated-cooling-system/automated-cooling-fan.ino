#include <LiquidCrystal.h>  // Standard LCD library

#define TEMP_PIN A0         // TMP sensor on analog pin A0
#define motorPin1 3         // L293D Input 1 (Pin 2)
#define motorPin2 4         // L293D Input 2 (Pin 7)
#define enablePin 5         // L293D Enable pin (Pin 1)

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  lcd.begin(16, 2);
  lcd.print("   Fan Speed  ");
  delay(2000);

  lcd.clear();
  lcd.print("CONTROLS SYSTEM");
  delay(2000);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  analogWrite(enablePin, 0);  // Ensure motor starts OFF
}

void loop() {
  int analogValue = analogRead(TEMP_PIN);  // Read TMP sensor
  float voltage = (analogValue / 1023.0) * 5.0;  // Convert to voltage (0-5V)
  float temp = (voltage - 0.5) * 100;  // Convert to Celsius (TMP36 logic)

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");

  int fanSpeed = 0;

  if (temp < 30) {
    fanSpeed = 0;
    lcd.setCursor(0, 1);
    lcd.print("Fan OFF      ");
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  } else if (temp >= 30 && temp <= 40) {
    fanSpeed = map(temp, 30, 40, 128, 255);
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: ");
    lcd.print((fanSpeed * 100) / 255);
    lcd.print("%");
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  } else {
    fanSpeed = 255;
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: 100%");
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  }

  analogWrite(enablePin, fanSpeed);  // PWM control for fan speed
  delay(3000);  // Wait to refresh
}

