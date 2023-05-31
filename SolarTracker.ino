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
  water_sensor_init();
}

/**
*   @brief Funzione di loop
*/
void loop(){
  Serial.println("MAIN: ");
  Serial.println(water_sensor_read_digital());
  delay(2000);
}