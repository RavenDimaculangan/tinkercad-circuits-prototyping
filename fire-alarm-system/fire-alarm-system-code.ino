#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int flat = 0;
float tempState = 0;
float VtoTemp = 0.0; 
float realTemp = 0.0;
const float V = 5.0;

const int buzzer = 2;
const int Led = 3;
const int TMP = A0;

void setup(){
  
  pinMode(buzzer, OUTPUT);
  pinMode(Led, OUTPUT);
  pinMode(TMP, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("SYSTEM READY.");
  delay(3000);
  lcd.clear();
  
  
}

void loop(){
  
  tempState = analogRead(TMP);
  VtoTemp = tempState * (V / 1023.0);
  realTemp = (VtoTemp - 0.500) * 100.0;
  flat = realTemp;
  
  lcd.setCursor(0, 1);
  lcd.print("Temp:          ");
  lcd.setCursor(6, 1);
  lcd.print(flat);
  lcd.print(" degC");
  delay(100);
  
  if (realTemp >= 60 && realTemp <= 70){
    
    digitalWrite(buzzer, HIGH);
    digitalWrite(Led, HIGH);
    lcd.setCursor(1, 0);
    lcd.print("POSSIBLE FIRE.");
    delay(1000); 
    digitalWrite(buzzer, LOW);
    digitalWrite(Led, LOW);
    lcd.clear();
    
  } else if(realTemp >= 71){
    
    digitalWrite(buzzer, HIGH);
    digitalWrite(Led, HIGH);
    lcd.setCursor(5, 0);
    lcd.print("FIRE!");
    delay(500); 
    digitalWrite(buzzer, LOW);
    digitalWrite(Led, LOW);
    lcd.clear();
    
  } else  {
    
    digitalWrite(buzzer, LOW);
    digitalWrite(Led, LOW);
    lcd.setCursor(4, 0);
    lcd.print("NO FIRE.");
    delay(1000);
    lcd.clear();
  
  }
  delay(100);
  
}

