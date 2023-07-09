/**
*   @file photoresistor.ino
*
*   @brief Logica che gestisce i fotoresistori.
*/

int pins[] = {PR_1, PR_2, PR_3, PR_4};/**< L'array contiene i GPIO collegati ai fotoresistori */
//avendo la torretta puntata contro
//pr1 sopra
//pr2 destra
//pr3 sotto
//pr4 sinistra


/**
*   @brief La funzione serve ad inizializzare i fotoresistori
*
*   @note La funzione va chiamata nel setup
*/
void photoresistor_init(){
  for(int i=0; i<4; i++){
    pinMode(pins[i], INPUT);
  }
}

/**
*   @brief La funzione riempi il parametro di input con i valori di tensione letti sulle fotoresistenze
*
*   @param values E' l'indirizzo di un array di 4 interi. Al termine della chiamata, l'array è conterrà i valori letti
*/
void photoresistor_get(int* values){
  for(int i=0; i<4; i++){
    values[i] = map(analogRead(pins[i]), 0, 1023, 0, 500);
  }
}