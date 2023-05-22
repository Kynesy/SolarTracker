//#include "C:\Users\cezar\Desktop\SolarTracker\clock_module.ino"

void setup() {
  Serial.begin(9600);
  clock_module_initialize();
  clock_module_set("Lun", 14, 55, 0, 22, 5, 2023);
}

void loop() {
  clock_module_get();
  delay(2000);
}
