#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("BALISONG");
  delay(4000);
  lcd.clear();
  
}

void loop()
{
  lcd.setCursor(2, 0);
  lcd.print("YOU");
  delay(250);
  lcd.setCursor(9, 0);
  lcd.print("ARE");
  delay(250);
  lcd.setCursor(2, 1);
  lcd.print("THE");
  delay(250);
  lcd.setCursor(6, 1);
  lcd.print("REASON");
  delay(250);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("I");
  delay(200);
  lcd.setCursor(2, 1);
  lcd.print("SMILE");
  delay(1100);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("YOU");
  delay(250);
  lcd.setCursor(8, 0);
  lcd.print("PUT");
  delay(250);
  lcd.setCursor(2, 1);
  lcd.print("THE");
  delay(250);
  lcd.setCursor(6, 1);
  lcd.print("WORTH");
  delay(250);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("IN");
  delay(300);
  lcd.setCursor(2, 1);
  lcd.print("MY");
  delay(300);
  lcd.setCursor(5, 0);
  lcd.print("WHILE");
  delay(500);
  lcd.setCursor(6, 1);
  lcd.print("BABY");
  delay(1500);
  lcd.clear();
  delay(1000);
  
  lcd.setCursor(2, 0);
  lcd.print("YOU'RE");
  delay(300);
  lcd.setCursor(2, 1);
  lcd.print("EVERYTHING");
  delay(600);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("I");
  delay(300);
  lcd.setCursor(2, 1);
  lcd.print("WANTED");
  delay(1600);
  lcd.clear();
  delay(2500);
  
  lcd.setCursor(2, 0);
  lcd.print("NEVER");
  delay(350);
  lcd.setCursor(8, 0);
  lcd.print("IN");
  delay(300);
  lcd.setCursor(2, 1);
  lcd.print("MY");
  delay(300);
  lcd.setCursor(6, 1);
  lcd.print("LIFE");
  delay(400);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("HAVE I");
  delay(700);
  lcd.setCursor(9, 0);
  lcd.print("BEEN");
  delay(600);
  lcd.setCursor(2, 1);
  lcd.print("MORE");
  delay(600);
  lcd.setCursor(9, 1);
  lcd.print("SURE");
  delay(2500);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("YOU'RE");
  delay(300);
  lcd.setCursor(2, 1);
  lcd.print("EVERYTHING");
  delay(600);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("I");
  delay(300);
  lcd.setCursor(2, 1);
  lcd.print("WANTED");
  delay(3000);
  lcd.clear();
}
