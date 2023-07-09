/**
*   @file clock_module.ino
*
*   @brief Logica che gestisce il modulo clock MH-2, con microcontrollore DS1302
*/

#include <DS1302.h>

/**
*   @brief Classe del modulo clock
*
*   Nel costruttore vanno passati:  \n
*   - pin di reset
*   - pin dei dati
*   - pin del clock
*/
DS1302 rtc(CM_RST_PIN, CM_DATA_PIN, CM_CLK_PIN);

/**
*   @brief Funzione di inizializzazione del modulo clock
*
*   @note La funzione va chiamata nel setup
*/
void clock_module_init()
{
  rtc.halt(false);
  rtc.writeProtect(false);
}

/**
*   @brief Funzione usata per impostare ora e data sul modulo clock
*
*   @param hour Intero che indica l'ora (formato 24h)
*   @param min Intero che indica il minuto
*   @param sec Intero che indica il secondo
*   @param day Intero che indica il giorno del mese
*   @param month Intero che indica il numero del mese
*   @param year Intero che indica l'anno
*/
void clock_module_set(int hour, int min, int sec, int day, int month, int year){
  rtc.setTime(hour, min, sec);
  rtc.setDate(day, month, year);
}


/**
*   @brief La funzione fornisce il giorno della settimana, l'ora e la data forniti dal modulo clock
*
*   @param week_day Parametro di output che indica il giorno della settimana attuale
*   @param time Parametro di output che indica l'ora attuale
*   @param date Parametro di output che indica la data attuale
*/
void clock_module_get(String& time, String& date) {
  time = rtc.getTimeStr();
  date = rtc.getDateStr();
}


