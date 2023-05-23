/*
CS    10
MOSI  11
MISO  12
SCK   13
*/

#include <SPI.h>
#include <SD.h>

//Time, Temperature, Pressure, Rain, SunCoord
File dataFile;
String fileName;

void sd_reader_init(String file_name){
  Serial.print("Initializing SD card...");
  fileName = file_name;
  if (!SD.begin(4)) {
    Serial.println("SD card initialization failed!");
  }
  Serial.println("SD card initialized.");

  String header = "Time,Temperature,Pressure,Rain\n";
  dataFile = SD.open(fileName, FILE_WRITE);
  dataFile.println(header);
  dataFile.close();
}

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