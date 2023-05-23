//#include "C:\Users\cezar\Desktop\SolarTracker\clock_module.ino"

void setup() {
  Serial.begin(9600);
  clock_module_init();
  clock_module_set("Lun", 0, 0, 0, 1, 1, 2000);
}

void loop() {
  Serial.print("IN MAIN: ");
  Serial.println(clock_module_get());
  delay(2000);
}
