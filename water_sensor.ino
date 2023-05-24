int water_presence = 0;

void water_sensor_init(){
  pinMode(WATER_SENSOR_PIN_DIGITAL, INPUT);
}


//ritorna 1 in caso di pioggia, 0 altrimenti
bool water_sensor_read_digital() {
  water_presence = digitalRead(WATER_SENSOR_PIN_DIGITAL);     // Legge il valore e lo si memorizza nella variabile livelloLiquido
  return water_presence ? true : false;                     // invia alla funzione chiamante il valore letto
}