#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int PIRstate = 0;

const int PIR = 7;
const int LBulb = 6;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  pinMode(PIR, INPUT);
  pinMode(LBulb, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("SYSTEM READY.");
  delay(3000);
  lcd.clear();
  

}

void loop(){
  
  PIRstate = digitalRead(PIR);
  
  if(PIRstate == 1){
    
    digitalWrite(LBulb, HIGH);
    
    
    lcd.setCursor(5, 0);
    lcd.print("MOTION");
    lcd.setCursor(3, 1);
    lcd.print("DETECTED.");
    
    delay(5000);
    lcd.clear();
    
  } else {
    
    digitalWrite(LBulb, LOW);
    
    
    lcd.setCursor(3, 0);
    lcd.print("NO MOTION");
    lcd.setCursor(3, 1);
    lcd.print("DETECTED.");
    delay(1000);
    lcd.clear();
    
  } 
  
  delay(100);
  
}



