void setup(){
  Serial.begin(9600);
  sd_reader_init("sium.csv");
}

void loop(){
  sd_reader_append("01/01/23", "25", "1", "0");
  delay(2000);
}