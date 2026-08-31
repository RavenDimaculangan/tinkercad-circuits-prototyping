#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup(){
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("NAIILANG");
  delay(3000);
  lcd.clear();
  
}


void loop(){
  
  lcd.setCursor(2, 0);
  lcd.print("TU");
  delay(800);
  lcd.setCursor(4, 0);
  lcd.print("MI");
  delay(800);
  lcd.setCursor(6, 0);
  lcd.print("NGIN");
  delay(400);
  lcd.setCursor(11, 0);
  lcd.print("KA");
  delay(400);
  
  lcd.setCursor(2, 1);
  lcd.print("SA");
  delay(400);
  lcd.setCursor(9, 1);
  lcd.print("AKIN");
  delay(1000);
  
  lcd.clear();
  delay(400);
  
  lcd.setCursor(2, 0);
  lcd.print("GUSTO");
  delay(800);
  lcd.setCursor(8, 0);
  lcd.print("KONG");
  delay(800);
  lcd.setCursor(2, 1);
  lcd.print("LINAWIN");
  delay(1000);
  
  lcd.clear();
  delay(600);
  
  lcd.setCursor(2, 0);
  lcd.print("NAIILANG");
  delay(1400);
  lcd.setCursor(2, 1);
  lcd.print("KA");
  delay(800);
  lcd.setCursor(5, 1);
  lcd.print("BA");
  delay(1000);
  
  lcd.clear();
  delay(200);
  
  lcd.setCursor(2, 0);
  lcd.print("'PAG");
  delay(600);
  lcd.setCursor(10, 0);
  lcd.print("TAYO");
  delay(600);
  lcd.setCursor(2, 1);
  lcd.print("LANG");
  delay(600);
  lcd.setCursor(7, 1);
  lcd.print("DALAWA?");
  delay(1000);
  
  lcd.clear();
  delay(400);
  
  lcd.setCursor(2, 0);
  lcd.print("SINASABI");
  delay(1200);
  lcd.setCursor(2, 1);
  lcd.print("KO");
  delay(600);
  lcd.setCursor(5, 1);
  lcd.print("NGA");
  delay(800);
  lcd.setCursor(9, 1);
  lcd.print("NA");
  delay(1000);
  
  lcd.clear();
  delay(200);
  
  lcd.setCursor(2, 0);
  lcd.print("ATIN");
  delay(600);
  lcd.setCursor(7, 0);
  lcd.print("ANG");
  delay(600);
  lcd.setCursor(2, 1);
  lcd.print("MUNDO");
  delay(1300);
  
  lcd.clear();
  delay(400);
  
  lcd.setCursor(2, 0);
  lcd.print("WALANG");
  delay(1200);
  lcd.setCursor(9, 0);
  lcd.print("IBANG");
  delay(800);
  lcd.setCursor(2, 1);
  lcd.print("TULAD");
  delay(1200);
  lcd.setCursor(9, 1);
  lcd.print("MO...");
  delay(3000);
  
  lcd.clear();
  delay(2000);
  
}
