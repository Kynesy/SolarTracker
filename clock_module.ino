#include <DS1302.h>
#include <string.h>

#define CM_CLOCK 5
#define CM_DATA 6
#define CM_RESET 7

DS1302 rtc(CM_RESET, CM_DATA, CM_CLOCK);

void clock_module_initialize(){
  // Imposta RTC in run-mode e disabilita la protezione da scrittura
  rtc.halt(false);
  rtc.writeProtect(false);
}

int dayToNum(char* day){
  if (strncmp(day, "Lun", 3)==0){
    return 1;
  }else if (strncmp(day, "Mar", 3)==0){
    return 2;
  }else if (strncmp(day, "Mer", 3)==0){
    return 3;
  }else if (strncmp(day, "Gio", 3)==0){
    return 4;
  }else if (strncmp(day, "Ven", 3)==0){
    return 5;
  }else if (strncmp(day, "Sab", 3)==0){
    return 6;
  }else if (strncmp(day, "Lun", 3)==0){
    return 7;
  }
  return 0;
}


void clock_module_set(char* week_day, int hour, int min, int sec, int day, int month, int year){
  rtc.halt(false);
  rtc.writeProtect(false);
  /*
  rtc.setDOW(dayToNum(day));
  rtc.setTime(hour, min, sec);
  rtc.setDate(day, month, year);
  */
  rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(6, 8, 2010);   // Set the date to August 6th, 2010
}

char* clock_module_get(){
  /*
  char* week_day = rtc.getDOWStr(FORMAT_SHORT);
  char* date = rtc.getDateStr();
  char* time = rtc.getTimeStr(FORMAT_SHORT);
  Serial.println(week_day);
  Serial.println(date);
  Serial.println(time);

  char result[80];
  strncmp(result, week_day, strlen(week_day));
  strncmp(result, date, strlen(date));
  strncmp(result, time, strlen(time));

  return result;
  */
  Serial.println(rtc.getTimeStr());
  
  // Display abbreviated Day-of-Week in the lower left corner
  Serial.println(rtc.getDOWStr());
  // Display date in the lower right corner
  Serial.println(rtc.getDateStr());
}
