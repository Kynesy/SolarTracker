#include <DS1302.h>

DS1302 rtc(CM_RST_PIN, CM_DATA_PIN, CM_CLK_PIN);

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

void clock_module_init()
{
  rtc.halt(false);
  rtc.writeProtect(false);
}

void clock_module_set(char* week_day, int hour, int min, int sec, int day, int month, int year){
  rtc.setDOW(dayToNum(week_day));
  rtc.setTime(hour, min, sec);
  rtc.setDate(day, month, year);
}

String clock_module_get_weekDay(){
  String week_day = rtc.getDOWStr(FORMAT_SHORT);
  return week_day;
}

String clock_module_get_time(){
  String time = rtc.getTimeStr(FORMAT_SHORT);
  return time;
}

String clock_module_get_date(){
  String date = rtc.getDateStr(FORMAT_SHORT, FORMAT_LITTLEENDIAN, '/');
  return date;
}