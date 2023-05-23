#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void lcd_init(){
  lcd.init();
  lcd.init();
  lcd.backlight();
}

void lcd_set(String time, String temperature, String pressure){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String("Time: " + time));

  lcd.setCursor(0, 1);
  lcd.print(String("T: " + temperature + " °C - P: " + pressure + "atm"));
}