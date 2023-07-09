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
*   @note La funzione va chiamata nel main
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
void sd_reader_append(String fileName, String time, String temperature, String pressure, String rain, String X_Angle, String Y_Angle) {
  String data = time + "," + temperature + "," + pressure + "," + rain + "," + X_Angle + "," + Y_Angle + "\n";

  File dataFile = SD.open(fileName, FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    Serial.println("SD: Data written to file.");
  } else {
    // If the file doesn't exist, create it and append the data
    dataFile = SD.open(fileName, FILE_WRITE);
    if (dataFile) {
      dataFile.println(data);
      dataFile.close();
      Serial.println("SD: Data written to new file.");
    } else {
      Serial.println("SD: Error opening file.");
    }
  }
}
