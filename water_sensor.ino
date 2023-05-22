#define WATER_SENSOR_PIN A0

int water_presence = 0;

void water_sensor_initialize(){
  pinMode(WATER_SENSOR_PIN, INPUT);
}


//ritorna 1 in caso di pioggia, 0 altrimenti
bool water_sensor_read() {
  water_presence = analogRead(WATER_SENSOR_PIN);      // Legge il valore e lo si memorizza nella variabile livelloLiquido
  return water_presence ? true : false;                     // invia alla funzione chiamante il valore letto
}
