/**
*   @file lcd_module.ino
*
*   @brief Logica che gestisce il display LCD
*   
*   Il display è collegato tramite I2C
*/

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); /**< Classe del modulo LCD */

/**
*   @brief Funzione di inizializzazione del modulo LCD
*
*   @note La funzione va richiamata nel setup
*/
void lcd_init(){
  lcd.init();
  lcd.init();
  lcd.backlight();
}

/**
*   @brief La funzione scrive sul display l'ora, la temperatura e la pressione
*
*   @param time Indica l'ora da mostrare
*   @param temperature Indica la temperatura da mostrare
*   @param pressure Indica la pressione da mostrare
*/
void lcd_set(String time, String temperature, String pressure){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String("Time: " + time));

  lcd.setCursor(0, 1);
  lcd.print(String("T: " + temperature + " °C - P: " + pressure + "atm"));
}