/**
*   @file water_sensor.ino
*
*   @brief Logica che gestisce il sensore di rilevazione di pioggia
*
*   @note Il sensore va collegato su pin digitale.
*/

/**
*   @brief Funzione di inizializzazione del sensore di pioggia.
*
*   @note La funzione va richiamata nel setup
*/
void water_sensor_init(){
  pinMode(WATER_SENSOR_PIN_DIGITAL, INPUT);
}


/**
*   @brief La funzione legge lo stato del sensore di pioggia
*
*   @return Restituisce 1 in caso di pioggia, 0 altrimenti
*/
bool water_sensor_read_digital() {
  int water_presence = digitalRead(WATER_SENSOR_PIN_DIGITAL);     // Legge il valore e lo si memorizza nella variabile livelloLiquido
  return water_presence ? true : false;                     // invia alla funzione chiamante il valore letto
}