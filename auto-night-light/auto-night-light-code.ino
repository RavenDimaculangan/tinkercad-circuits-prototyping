#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int PhotR = 4;
const int Lbulb = 2;
int photState = 0;

void setup(){
  
  pinMode(PhotR, INPUT);
  pinMode (Lbulb, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("SYSTEM READY.");
  delay(3000);
  lcd.clear();
  
  
}


void loop(){
  
  photState = digitalRead(PhotR);
  
  if(photState == 0){
    digitalWrite(Lbulb, HIGH);
    lcd.setCursor(5, 0);
    lcd.print("NIGHT.");
    delay(1000);
    lcd.clear();
  } else {
    digitalWrite(Lbulb, LOW);
    lcd.setCursor(6, 0);
    lcd.print("DAY.");
    delay(1000);
    lcd.clear();
  }
  delay(100);
  
}
