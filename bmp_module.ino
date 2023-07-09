/**
*   @file bmp_module.ino
*
*   @brief Logica che gestisce il sensore BMP280
*
*   @note Il sensore è collegato tramite I2C e va alimentato a 3.3 V
*/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP280_ADDRESS 0x76 /**< Indirizzo I2C del sensore BMP280 */
Adafruit_BMP280 bmp; /**< Classe del sensore BMP280 */

/**
*   @brief La funzione serve a inizializzare il sensore.
*
*   @note Deve essere richiamata nel setup
*/
void bmp_module_init() {
  unsigned status;
  status = bmp.begin(BMP280_ADDRESS);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  
  /* Default settings from the datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

/**
*   @brief La funzione serve per restituire i valori di pressione e temperatura.
*
*   @param temperature E' un parametro di output che conterrà la temperatura registrata in gradi celsius
*   @param pressure E' un parametro di output che conterrà la pressione registrata in hPascal
*/
void bmp_module_get(float* temperature, float* pressure){
  *temperature = bmp.readTemperature();
  *pressure = bmp.readPressure() / 100;
}