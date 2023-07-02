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
}

/**
*   @brief Funzione di loop
*/
void loop(){
  int values[4];
  photoresistor_get(values);

  Serial.println(String(values[0]) + " " + String(values[1]) + " " + String(values[2]) + " " + String(values[3]));
  if(values[0] > 20 || values[2] > 20){
    if(values[0] > values[2]){
      //muovi su
      Y_moveUp();
      Serial.println("SU: " + String(values[0]) + " > " + String(values[2]));
    }else{
      Serial.println("GIU: " + String(values[0]) + " < " + String(values[2]));
      //muovi giù
      Y_moveDown();
    }
  }

  if(values[1] > 20 || values[3] > 20){
    if(values[1] < values[3]){
      //muovi sinistra
      Serial.println("Sinistra: " + String(values[1]) + " < " + String(values[3]));
      XmoveClockwise();
    }else{
      //muovi destra
      Serial.println("Destra: " + String(values[1]) + " > " + String(values[3]));
      XmoveAnticlockwise();
    }
  }

  delay(500);
}