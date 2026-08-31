#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int servoPin = 5;
const int trigPin = 2;
const int echoPin = A0;

int distance = 0;

Servo myServo;

void setup(){
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("System Ready.");
  delay(3000);
  lcd.clear();
  
  myServo.attach(servoPin);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  

}

void loop(){
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.0344 / 2;
  
  lcd.setCursor(0, 0);
  lcd.print("Distance:           ");
  lcd.setCursor(10, 0);
  lcd.print(distance);
  lcd.print("cm");
  
  openTcan();
  
  delay(500);
  

}

void openTcan(){
  
  if (distance <= 25){
    myServo.write(90);
    delay(5000);
  }
  else if(distance >=26){
    myServo.write(0);
  }
  
}
