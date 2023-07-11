/**
*   @file sd_reader.ino
*
*   @brief Logica che gestisce il lettore di MicroSD
*
*   Il sensore è collegato con SPI :
*   - CS    10
*   - MOSI  11
*   - MISO  12
*   - SCK   13
*/

#include "SPI.h"
#include "SD.h"

/**
*   @brief La funzione inizializza il lettore di schede MicroSD
*
*   @note La funzione va chiamata nel setup
*/
void sd_reader_init(){
   Serial.print("Initializing SD card...");

  if (!SD.begin(SD_PIN)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

/**
*   @brief La funzione è usata per appendere righe nel file CSV.
*
*   @param fileName Nome del file da creare
*   @param time Timestamp della rilevazione
*   @param temperature Valore della temperatura
*   @param pressure Valore della pressione
*   @param rain Vale "0" (non piove) o "1" (piove)
*   @param X_Angle Angolo orizzontale
*   @param Y_Angle Angolo Verticale
*/
void sd_reader_append(char* name, String time, float temperature, float pressure, int rain, int X_Angle, int Y_Angle){
  File myFile = SD.open(name, FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to " + String(name) +"...");
    myFile.println(time + "," + String(temperature) + "," + String(pressure) + "," + String(rain) + "," + String(X_Angle) + "," + String(Y_Angle));
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening "+ String(name));
  }
}