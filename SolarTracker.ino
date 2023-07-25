/**
 * @file SolarTracker.ino
 * @brief Main program file for Sun Tracker System.
 */
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "SD.h"
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>

//MAPPING GPIO
#define CM_CLK_PIN 3 /**< Clock pin for Clock Module  */
#define CM_DATA_PIN 4 /**< Data pin for Clock Module */
#define CM_RST_PIN 7 /**< Reset pin for Clock Module */
#define SD_SELECT 10 /**< ChipSelect for MicroSD Card Adapter - MOSI 11, MISO 12, SCK 13 */
#define UP A0 /**< Analog Pin for UP photoresistor */
#define DX A1   /**< Analog Pin for RIGHT photoresistor */
#define SX A2 /**< Analog Pin for LEFT photoresistor  */
#define DW A3 /**<  Analog Pin for DOWN photoresistor  */
#define WATER_SENSOR_PIN_DIGITAL 8 /**< Digital Pin Of Water Sensor */
#define SERVO_X_PIN 5 /**< Digital pin for Horizontal Servo */
#define SERVO_Y_PIN 6 /**< Digital pin for Vertical Servo */

//CONSTANTS
#define MAX_INTERVAL 5000 /**< Maximum interval for data update in milliseconds. */
const int threeshold = 15; /**< Threshold value for sun tracking servo control. */
LiquidCrystal_I2C lcd(0x27, 16, 2); /**< LCD module object. */
Adafruit_BMP280 bmp; /**< BMP280 sensor object. */
DS1302 rtc(CM_RST_PIN, CM_DATA_PIN, CM_CLK_PIN); /**< Real-time clock module object. */
char* fileName = "dati1.csv"; /**< File name used to store data on SD */
File file; /**< File Object */

//VARIABLES
int startInterval; /**< Stores the starting interval time */
float temperature; /**< Stores the temperature value in Celsius degrees */
float pressure; /**< Stores the pressure value in hPa */
bool isRaining; /**< Stores the raining value: 1 if is raining, 0 otherwise */
int x_angle; /**< Stores the horizontal angle of the Servo_X */
int y_angle; /**< Stores the vertical angle of the Servo_Y */

// Function prototypes
void setup();
void loop();

// Sun tracking functions
void sun_find();
void sun_follow();

// SD module functions
static void sd_init();
static void sd_write();
static void sd_read();

// LCD module functions
void lcd_init();
void lcd_update();

// BMP280 module functions
void bmp_init();
void bmp_update();

// Real-time clock module function
void clock_init(int hour, int min, int sec, int day, int month, int year);

// Water sensor functions
void water_sensor_init();
void water_sensor_update();

// Photoresistor function
void photoresistor_init();

// Servo module functions
static void servo_init();
void X_moveSx();
void X_moveDx();
void Y_moveDown();
void Y_moveUp();
void generatePWM(int servo, unsigned long pulseWidth);

/**
 * @brief Setup function for the Arduino sketch.
 */
void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize modules and sensors
  bmp_init();
  lcd_init();
  clock_init(16, 0, 0, 25, 7, 2023);
  water_sensor_init();
  photoresistor_init();
  servo_init();
  sd_init();
  sun_find();
  startInterval = millis();
}


/**
 * @brief Loop function for the Arduino sketch.
 */
void loop() {
  sun_follow();
  // Perform data update after a certain interval
  int tmpInterval = millis();
  if(tmpInterval - startInterval > MAX_INTERVAL){
    water_sensor_update();
    bmp_update();
    lcd_update();
    sd_write();
    sd_read();
    startInterval = millis();
  }
  delay(100);
}

/**
 * @brief Rotate the solar panel to find the sun's position.
 * 
 * This function rotates the solar panel horizontally to find the sun's position.
 * It starts by moving the panel upward until it reaches a certain angle, and then
 * it continuously rotates the panel left and right to detect the direction of the sun.
 * Once it identifies the sun's direction, it stops and keeps the solar panel facing the sun.
 * This function assumes the presence of analog photoresistors connected to the pins UP and DX,
 * representing the left and right photoresistors, respectively.
 */
void sun_find(){
  int sx=0;
  int dx=0;

  while(y_angle < 50){
    Y_moveUp();
  }

  while(true){
    if(analogRead(DX) < analogRead(SX)){
      if(sx==1){
        break;
      }
      X_moveDx();
      sx=0;
      dx=1;
    }else{
      if(dx==1){
        break;
      }
      X_moveDx();
      sx=1;
      dx=0;
    }
  }
}

/**
 * @brief Continuously track the sun's position and adjust the solar panel.
 * 
 * This function continuously tracks the sun's position and makes adjustments to keep
 * the solar panel facing the sun. It uses analog photoresistors connected to the pins SX and DX
 * to detect the intensity of sunlight on the left and right sides, respectively.
 * Based on the readings, it decides whether to rotate the panel left or right to keep the sun
 * at the center. It also uses a threshold value to determine the required adjustment.
 * Additionally, it uses analog photoresistors connected to the pins UP and DW to detect the
 * intensity of sunlight on the upper and lower sides, respectively. It adjusts the panel's
 * vertical position accordingly to keep the sunlight balanced between the upper and lower sides.
 */
void sun_follow(){
  if(analogRead(DX) < analogRead(SX) - threeshold){
    X_moveDx();
  }else if(analogRead(DX) > analogRead(SX) + threeshold){
    X_moveSx();
  }

  if(analogRead(UP) < analogRead(DW) - threeshold){
    Y_moveUp();
  }else if(analogRead(UP)> analogRead(DW) + threeshold){
    Y_moveDown();
  }
}

/**
 * @brief Initialize the SD module.
 * 
 * This function initializes the SD module and checks if the initialization
 * was successful. It uses the SD_SELECT pin defined in the global constants.
 */
static void sd_init(){
  if (!SD.begin(SD_SELECT)) {
    Serial.println("SD | Errore inizializzazione");
    while (1);
  }
  Serial.println("SD | Successo inizializzazione");
}

/**
 * @brief Write data to the SD card.
 * 
 * This function opens a file on the SD card and writes data to it in CSV format.
 * It includes data such as time, temperature, pressure, rain status, and the angles
 * of the servomotors. If the rain sensor is activated, the angles are set to fixed
 * values (0 degrees for horizontal and 90 degrees for vertical).
 */
static void sd_write(){
  file = SD.open(fileName, FILE_WRITE);

  if (file) {
    if(isRaining){
      file.println(String(rtc.getTimeStr()) + "-" + String(rtc.getDateStr()) + "," + String(temperature) + "," + String(pressure) + "," + String(isRaining) + "," + "0" + "," + "90"); 
    }else{
      file.println(String(rtc.getTimeStr()) + "-" + String(rtc.getDateStr()) + "," + String(temperature) + "," + String(pressure) + "," + String(isRaining) + "," + String(x_angle) + "," + String(y_angle));
    }
    file.close();
    Serial.println("SD | Scrittura su file riuscita");
  } else {
    Serial.println("SD | Errore apertura file");
  }
}

/**
 * @brief Read data from the SD card.
 * 
 * This function reads data from the SD card and prints it to the Serial monitor.
 * Note: This function is not used in the main loop, but it is useful for debug.
 */
static void sd_read(){
  file = SD.open(fileName);
  if (file) {
    Serial.println("SD | Lettura file");
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  } else {
    Serial.println("SD | Errore lettura file");
  }
}

/**
 * @brief Initialize the LCD module.
 * 
 * This function initializes the LiquidCrystal_I2C module for the LCD display.
 * It sets up the I2C communication and initializes the LCD with backlight.
 */
void lcd_init(){
  lcd.init();
  lcd.init();
  lcd.backlight();

  Serial.println("LCD| Successo inizializzazione");
}

/**
 * @brief Update the LCD display with new data.
 * 
 * This function updates the content displayed on the LCD. It shows the current
 * time, temperature, pressure, and whether it's raining or sunny.
 */
void lcd_update(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(rtc.getTimeStr()) + " " + String(temperature) + "*C");

  lcd.setCursor(0, 1);
  if(isRaining){
    lcd.print(String(pressure) + "hPa" + "  Rain");
  }else{
    lcd.print(String(pressure) + "hPa" + "  Sun");
  }
}

/**
 * @brief Initialize the BMP280 module.
 * 
 * This function initializes the BMP280 sensor and checks if the initialization
 * was successful. It sets the operating mode, oversampling, and filtering options.
 */
void bmp_init() {
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println("BMP| Errore inizializzazione");

    while (1) delay(10);
  }else{
    Serial.println("BMP| Successo inizializzazione");
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

/**
 * @brief Update BMP280 sensor data.
 * 
 * This function reads temperature and pressure data from the BMP280 sensor.
 * It stores the values in the global variables temperature and pressure.
 */
void bmp_update(){
  temperature = bmp.readTemperature();
  pressure = bmp.readPressure()/100;
}

/**
 * @brief Initialize the real-time clock module (DS1302).
 * 
 * This function initializes the DS1302 real-time clock module with the provided date
 * and time values. It configures the clock to run continuously.
 * 
 * @param hour The hour value to set on the clock (0-23).
 * @param min The minute value to set on the clock (0-59).
 * @param sec The second value to set on the clock (0-59).
 * @param day The day value to set on the clock (1-31).
 * @param month The month value to set on the clock (1-12).
 * @param year The year value to set on the clock (e.g., 2023).
 */
void clock_init(int hour, int min, int sec, int day, int month, int year){
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setTime(hour, min, sec);
  rtc.setDate(day, month, year);

  Serial.println("CLK| Successo inizializzazione");
}

/**
 * @brief Initialize the water sensor.
 * 
 * This function initializes the water sensor pin as an input and sets up
 * the sensor to detect the presence of water (rain).
 */
void water_sensor_init(){
  pinMode(WATER_SENSOR_PIN_DIGITAL, INPUT);
  Serial.println("WTR| Successo inizializzazione");
}

/**
 * @brief Update the water sensor status.
 * 
 * This function reads the digital value from the water sensor pin and determines
 * whether it's raining or not. It updates the global variable isRaining accordingly.
 */
void water_sensor_update() {
  int water_presence = digitalRead(WATER_SENSOR_PIN_DIGITAL);
  isRaining = water_presence ? true : false;
}

/**
 * @brief Initialize the photoresistor.
 * 
 * This function initializes the pins connected to the photoresistors as inputs.
 */
void photoresistor_init(){
  pinMode(UP, INPUT);
  pinMode(DW, INPUT);
  pinMode(SX, INPUT);
  pinMode(DX, INPUT);
  Serial.println("PR | Successo inizializzazione");
}

/**
 * @brief Initialize the servo motors.
 * 
 * This function initializes the servo motors by setting the initial angles to zero.
 * It configures the servo motor pins as outputs.
 */
static void servo_init() {
  x_angle = 0;
  y_angle = 0;

  pinMode(SERVO_X_PIN, OUTPUT);
  pinMode(SERVO_Y_PIN, OUTPUT);
  
  Serial.println("SRV| Successo inizializzazione");
}

/**
 * @brief Rotate the X-axis servo motor to the left (counter-clockwise).
 * 
 * This function rotates the X-axis servo motor to the left (counter-clockwise)
 * by a fixed angle. It updates the global variable x_angle to keep track of
 * the current angle of the servo motor.
 */
void X_moveSx(){
  generatePWM(SERVO_X_PIN, 1183);
  x_angle += 10;
  if(x_angle == 360){
    x_angle = 0;
  }
  delay(100);
}

/**
 * @brief Rotate the X-axis servo motor to the right (clockwise).
 * 
 * This function rotates the X-axis servo motor to the right (clockwise)
 * by a fixed angle. It updates the global variable x_angle to keep track of
 * the current angle of the servo motor.
 */
void X_moveDx(){
  generatePWM(SERVO_X_PIN, 1840);

  x_angle -= 10;
  if(x_angle == -360){
    x_angle = 0;
  }
  delay(100);
}

/**
 * @brief Rotate the Y-axis servo motor downward.
 * 
 * This function rotates the Y-axis servo motor downward by a fixed angle.
 * It updates the global variable y_angle to keep track of the current angle
 * of the servo motor.
 */
void Y_moveDown(){
  if(y_angle >= 10){
    generatePWM(SERVO_Y_PIN, 1270);
    y_angle -= 10;
    delay(100);
  }
}

/**
 * @brief Rotate the Y-axis servo motor upward.
 * 
 * This function rotates the Y-axis servo motor upward by a fixed angle.
 * It updates the global variable y_angle to keep track of the current angle
 * of the servo motor.
 */
void Y_moveUp(){
  if(y_angle <= 80){
    generatePWM(SERVO_Y_PIN, 1780);
    y_angle += 10;
    delay(100);
  }
}

/**
 * @brief Generate PWM signal for servo motor control.
 * 
 * This function generates the PWM signal required to control the servo motors.
 * It sets the specified servo pin high for a certain pulse width and then low
 * for the remaining period to achieve the desired angle of the servo motor.
 * 
 * @param servo The pin number of the servo motor.
 * @param pulseWidth The duration (in microseconds) the PWM signal should be high.
 */
void generatePWM(int servo, unsigned long pulseWidth) {
  digitalWrite(servo, HIGH);    // Set the PWM pin high
  delayMicroseconds(pulseWidth);  // Keep it high for the specified pulse width
  digitalWrite(servo, LOW);     // Set the PWM pin low
  delayMicroseconds(20000- pulseWidth);  // Keep it low for the remaining period (20 ms - pulse width)
}
