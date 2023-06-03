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
  servos_init();
}

/**
*   @brief Funzione di loop
*/
void loop(){
  servos_set(90, 90);
  delay(5000);
}