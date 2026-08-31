#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("MALAY KO");
  delay(3000);
  lcd.clear();
  
}

void loop(){
  
  lcd.setCursor(2, 0);
  lcd.print("IKAW");
  delay(500);
  lcd.setCursor(7, 0);
  lcd.print("PA");
  delay(200);
  lcd.setCursor(2, 1);
  lcd.print("RIN");
  delay(500);
  lcd.setCursor(6, 1);
  lcd.print("ANG");
  delay(500);
  
  lcd.clear();
  delay(400);
  
  lcd.setCursor(2, 0);
  lcd.print("NA");
  delay(500);
  lcd.setCursor(4, 0);
  lcd.print("KI");
  delay(600);
  lcd.setCursor(6, 0);
  lcd.print("KI");
  delay(700);
  lcd.setCursor(8, 0);
  lcd.print("TA");
  delay(600);
  
  lcd.clear();
  delay(900);
  
  lcd.setCursor(2, 0);
  lcd.print("ANG");
  delay(600);
  lcd.setCursor(2, 1);
  lcd.print("YAKAP");
  delay(600);
  lcd.setCursor(8, 1);
  lcd.print("MO");
  delay(600);
  
  lcd.clear();
  delay(1500);
  
  lcd.setCursor(2, 0);
  lcd.print("HANAP");
  delay(800);
  lcd.setCursor(9, 0);
  lcd.print("KO");
  delay(900);
  lcd.setCursor(2, 1);
  lcd.print("SA");
  delay(700);
  lcd.setCursor(5, 1);
  lcd.print("T'WINA");
  delay(2500);
  
  lcd.clear();
  delay(1500);
  
  lcd.setCursor(2, 0);
  lcd.print("AKO'Y");
  delay(900);
  lcd.setCursor(2, 1);
  lcd.print("NAG");
  delay(750);
  lcd.setCursor(8, 1);
  lcd.print("TATAKA");
  delay(2700);
  lcd.setCursor(8, 0);
  lcd.print("NAIIBA");
  delay(2900);
  
  lcd.clear();
  delay(800);
  
  lcd.setCursor(2, 0);
  lcd.print("ANG");
  delay(900);
  lcd.setCursor(6, 0);
  lcd.print("AKING");
  delay(1200);
  lcd.setCursor(2, 1);
  lcd.print("NA");
  delay(200);
  lcd.setCursor(5, 1);
  lcd.print("DARAMA");
  delay(2500);
  
  
  lcd.clear();
  delay(600);
  
  lcd.setCursor(2, 0);
  lcd.print("BUHAY");
  delay(1000);
  lcd.setCursor(8, 0);
  lcd.print("KO'Y");
  delay(1500);
  lcd.setCursor(2, 1);
  lcd.print("NAGKAGULO");
  delay(2400);
  
  lcd.clear();
  delay(900);
  
  lcd.setCursor(2, 0);
  lcd.print("MULA");
  delay(900);
  lcd.setCursor(2, 1);
  lcd.print("NANG");
  delay(400);
  lcd.setCursor(7, 1);
  lcd.print("IKA'Y");
  delay(900);
  
  lcd.clear();
  delay(600);
  
  lcd.setCursor(2, 0);
  lcd.print("IWANAN");
  delay(800);
  lcd.setCursor(2, 1);
  lcd.print("KO...");
  
  delay(3000);
  
  lcd.clear();
  delay(2000);
  
}
