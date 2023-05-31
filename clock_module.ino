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
*   @brief Funzione usata per convertire il giorno in formato stringa, nel corrispondente intero.
*
*   @param day Stringa contenente il giorno in formato breve ("Lun", "Mar", "Mer", "Gio", "Ven", "Sab", "Dom")
*
*   @note La funzione non va usata direttamente, ma serve ai fini della logica della funzione clock_module_set
*/
int dayToNum(char* day){
  if(strncmp("Lun", day, 3) == 0){
    return 1;
  }else if(strncmp("Mar", day, 3) == 0){
    return 2;
  }else if(strncmp("Mer", day, 3) == 0){
    return 3;
  }else if(strncmp("Gio", day, 3) == 0){
    return 4;
  }else if(strncmp("Ven", day, 3) == 0){
    return 5;
  }else if(strncmp("Sab", day, 3) == 0){
    return 6;
  }else if(strncmp("Dom", day, 3) == 0){
    return 7;
  }
  return 0;
}


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
*   @param week_day Stringa che indica il giorno in formato breve
*   @param hour Intero che indica l'ora (formato 24h)
*   @param min Intero che indica il minuto
*   @param sec Intero che indica il secondo
*   @param day Intero che indica il giorno del mese
*   @param month Intero che indica il numero del mese
*   @param year Intero che indica l'anno
*/
void clock_module_set(char* week_day, int hour, int min, int sec, int day, int month, int year){
  rtc.setDOW(dayToNum(week_day));
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
void clock_module_get(char* week_day, char* time, char* date){
  char* wd = rtc.getDOWStr(FORMAT_SHORT);
  char* t = rtc.getTimeStr(FORMAT_SHORT);
  char* d = rtc.getDateStr(FORMAT_SHORT, FORMAT_LITTLEENDIAN, '/');
  strncpy(week_day, wd, strlen(wd));
  strncpy(time, t, strlen(t));
  strncpy(date, d, strlen(d));
}