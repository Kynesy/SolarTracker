int pins[] = {PR_1, PR_2, PR_3, PR_4};

void photoresistor_init(){
  for(int i=0; i<4; i++){
    pinMode(pins[i], INPUT);
  }
}

int* photoresistor_get(){
  int values[4];
  for(int i=0; i<4; i++){
    values[i] = map(analogRead(pins[i]), 0, 1023, 0, 5);
  }

  return values; 
}