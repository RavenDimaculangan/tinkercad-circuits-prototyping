#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("NANDITO AKO");
  delay(4000);
  lcd.clear();
  
}

void loop()
{
  lcd.setCursor(2, 0);
  lcd.print("NANDITO");
  delay(1800);
  lcd.setCursor(11, 0);
  lcd.print("AKO");
  delay(1800);
  lcd.setCursor(2, 1);
  lcd.print("UMIIBIG");
  delay(1800);
  lcd.setCursor(10, 1);
  lcd.print("SAYO");
  delay(1400);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("KAHIT");
  delay(1000);
  lcd.setCursor(2, 1);
  lcd.print("NA");
  delay(1200);
  lcd.setCursor(8, 0);
  lcd.print("NAG");
  delay(700);
  lcd.setCursor(5, 1);
  lcd.print("DURUGO");
  delay(1000);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("ANG");
  delay(800);
  lcd.setCursor(2, 1);
  lcd.print("PUSO");
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("AT");
  delay(700);
  lcd.setCursor(2, 1);
  lcd.print("KUNG");
  delay(700);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("SAKALING");
  delay(1800);
  lcd.setCursor(2, 1);
  lcd.print("IWANAN");
  delay(1700);  
  lcd.setCursor(11, 0);
  lcd.print("KA");
  delay(400);
  lcd.setCursor(10, 1);
  lcd.print("NYA");
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("'WAG");
  delay(700);
  lcd.setCursor(7, 0);
  lcd.print("KANG");  
  delay(700);
  lcd.setCursor(2, 1);
  lcd.print("MAG-ALALA");
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("MAY");
  delay(700);
  lcd.setCursor(2, 1);
  lcd.print("NAG");
  delay(700);
  lcd.setCursor(6, 0);
  lcd.print("MAMAHAL");
  delay(800);
  lcd.setCursor(8, 1);
  lcd.print("SA'YO");
  delay(700);
  lcd.clear();
  
  lcd.setCursor(2, 0);
  lcd.print("NANDITO");
  delay(1800);
  lcd.setCursor(10, 0);
  lcd.print("AKO");
  delay(3000);
  lcd.clear();
}
