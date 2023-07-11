/**
*   @file SolarTracker.ino
*
*   @brief Il file contiene la logica principale del progetto.
*/

/**
*   @brief Funzione di setup
*/
#include <SPI.h>
#include <SD.h>

#define CM_CLK_PIN 3 /**< Clock pin del modulo clock */
#define CM_DATA_PIN 4 /**< Data pin del modulo clock */
#define CM_RST_PIN 7 /**< Reset pin del modulo clock */

#define SD_PIN 10 /**< ChipSelect pin del modulo MicroSD */

#define PR_1 A0 /**< Pin analogico del fotoresistore 1 */
#define PR_2 A1 /**< Pin analogico del fotoresistore 2 */
#define PR_3 A2 /**< Pin analogico del fotoresistore 3 */
#define PR_4 A3 /**< Pin analogico del fotoresistore 4 */

#define WATER_SENSOR_PIN_DIGITAL 8 /**< Pin digitale del sensore di pioggia */

#define SERVO_X_PIN 5 /**< Pin del servomotore orizzontale */
#define SERVO_Y_PIN 6 /**< Pin del servomotore verticale */

char* fileName = "data11.csv";
int x_angle, y_angle;
int startTime;
int threeshold = 10;

void setup(){
  Serial.begin(9600);

  photoresistor_init();
  bmp_module_init();
  lcd_init();
  water_sensor_init();
  servos_init(&x_angle, &y_angle);
  sun_find();
  clock_module_init();
  clock_module_set(13, 57, 0, 9, 7, 2023);
  Serial.println("Sium");
  startTime = millis();
}

/**
*   @brief Funzione di loop
*/
void loop(){
  int tmpTime = millis();
  float temp, press;
  int rain;
  String my_time;
  String my_date;
    Serial.println("Sium");
  if(tmpTime - startTime > 5000){
    //scrivi su file
  clock_module_get(my_time, my_date);
  bmp_module_get(&temp, &press);
  rain = water_sensor_read_digital();
  
  Serial.println("");
  Serial.println("X: " + String(x_angle) + " -- Y: " + String(y_angle));
  Serial.println("Rain: " + String(rain));
  Serial.println("Temp: " + String(temp) + " - Press: " + String(press));
  Serial.println(my_time);
  Serial.println(my_date);

  lcd_set(my_time, String(temp), String(press), rain);
  //sd_reader_append(fileName, "time", 1, 2, 3, 4, 5);
  startTime = millis();
  }
  
  sun_follow();
  delay(100);
}

void sun_find(){
  int values[4];
  int sx=0;
  int dx=0;

  while(true){
    photoresistor_get(values);

    if(values[3] < values[2]){
      //ruota antiorario
      if(sx==1){
        break;
      }
      X_moveAnticlockwise(&x_angle);
      sx=0;
      dx=1;
    }else{
      //ruota orario
      if(dx==1){
        break;
      }
      X_moveClockwise(&x_angle);
      sx=1;
      dx=0;
    }
  }
}

void sun_follow(){
  int values[4];
  photoresistor_get(values);

  //Serial.println(String(values[0]) + " - " + String(values[1]) + " - " + String(values[2]) + " - " + String(values[3]));

  if(values[1] < values[3] - threeshold){
    //move anticlock
    X_moveClockwise(&x_angle);
  }else if(values[1] > values[3] + threeshold){
    //move clock
    X_moveAnticlockwise(&x_angle);

  }

  if(values[0] < values[2] - threeshold){
    //move up
    Y_moveUp(&y_angle);
  }else if(values[0] > values[2] + threeshold){
    //move down
    Y_moveDown(&y_angle);
  }

}