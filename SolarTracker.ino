/**
*   @file SolarTracker.ino
*
*   @brief Il file contiene la logica principale del progetto.
*/

/**
*   @brief Funzione di setup
*/
#include "C:\Users\cezar\Desktop\SolarTracker\mapping.ino"

void setup(){
  Serial.begin(9600);

  photoresistor_init();
  servos_init();
  bmp_module_init();
  lcd_init();
  water_sensor_init();
  servos_init();
  clock_module_init();
  clock_module_set(1, 13, 57, 0, 9, 7, 2023);
}

/**
*   @brief Funzione di loop
*/
void loop(){
  Serial.println("");

  int values[4];
  float temp, press;
  int rain;
  String my_week_day;
  String my_time;
  String my_date;
  int x_angle, y_angle;

  clock_module_get(my_week_day, my_time, my_date);
  photoresistor_get(values);
  bmp_module_get(&temp, &press);
  rain = water_sensor_read_digital();
  servos_get(&x_angle, &y_angle);

  lcd_set(my_time, String(temp), String(press), rain);

  Serial.println("X: " + String(x_angle) + " -- Y: " + String(y_angle));
  Serial.println("Rain: " + String(rain));
  Serial.println("Temp: " + String(temp) + " - Press: " + String(press));
  Serial.println(String(values[0]) + " " + String(values[1]) + " " + String(values[2]) + " " + String(values[3]));
  Serial.println(my_week_day);
  Serial.println(my_time);
  Serial.println(my_date);

  delay(3000);
}



