//MAPPING GPIO
//-----------------------
//BMP280
//I2C
//-----------------------
//CLOCK_MODULE
#define CM_CLK_PIN 2
#define CM_DATA_PIN 4
#define CM_RST_PIN 7
//-----------------------
//SD_CARD_ADAPTER
#define SD_PIN 10
//-----------------------
//PHOTORESISTOR
#define PR_1 A0
#define PR_2 A1
#define PR_3 A2
#define PR_4 A3
//-----------------------
//WATER_SENSOR
#define WATER_SENSOR_PIN_DIGITAL 8
//-----------------------
//LCD_MODULE
//I2C
//-----------------------
//SERVOS
#define SERVO_X_PIN 5
#define SERVO_Y_PIN 6

void setup(){
  Serial.begin(9600);
  water_sensor_init();
}

void loop(){
  Serial.println("MAIN: ");
  Serial.println(water_sensor_read_digital());
  delay(2000);
}