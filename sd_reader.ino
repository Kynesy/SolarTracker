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

#include <SPI.h>
#include <SD.h>

File dataFile; /**< Classe che contiene il file su cui si scrive */
String fileName; /**< Nome del file che verrà scritto sulla SD */

/**
*   @brief La funzione inizializza il lettore di schede MicroSD
*
*   @param file_name Indica il nome del file da scrivere. Il file deve avere estensione .csv
*
*   Se il file esiste già sulla SD, viene prima rimosso e se ne crea un altro.
*
*   @note La funzione va chiamata nel main
*/
void sd_reader_init(String file_name){
    Serial.print("Initializing SD card...");
  fileName = file_name;

  if (!SD.begin(SD_PIN)) {
    Serial.println("SD card initialization failed!");
    while(1);
  }
  Serial.println("SD card initialized.");

  String header = "Time,Temperature,Pressure,Rain\n";

  if (SD.exists(fileName)) {
    Serial.print(fileName);
    Serial.println(" already exists.");
    SD.remove(fileName);
    Serial.print(fileName);
    Serial.println(" è stato rimosso.");
  }

  dataFile = SD.open(fileName, FILE_WRITE);
  Serial.print(fileName);
  Serial.println(" e' stato creato.");
  dataFile.println(header);
  dataFile.close();
}

/**
*   @brief La funzione è usata per appendere righe nel file CSV.
*
*   @param time Timestamp della rilevazione
*   @param temperature Valore della temperatura
*   @param pressure Valore della pressione
*   @param rain Vale "0" (non piove) o "1" (piove)
*/
void sd_reader_append(String time, String temperature, String pressure, String rain){
  String data = time + "," + temperature + "," + pressure + "," + rain + "\n";
  
  dataFile = SD.open(fileName, FILE_WRITE);
  if (dataFile) {
    dataFile.println(data);
    dataFile.close();
    Serial.println("Data written to file.");
  } else {
    Serial.println("Error opening file.");
  }
}