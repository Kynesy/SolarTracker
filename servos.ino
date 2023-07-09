/**
*   @file servos.ino
*
*   @brief Logica che gestisce il movimento del servomotori
*/

#include <Servo.h>

Servo servo1; /**< Classe del servomotore 1 - movimento lungo l'asse orizzontale*/
Servo servo2; /**< Classe del servomotore 2 - movimento lungo l'asse verticale*/

#define SPEED_CLOCKWISE 60
#define SPEED_ANTICLOCKWISE 120

#define STOP 90
#define PERIOD 1080

/**
*   @brief La funzione inizializza i servomotori
*
*   @note La funzione va richiamata nel setup
*/
void servos_init(int* x_angle, int* y_angle) {
  servo1.attach(SERVO_X_PIN); // attach servo 1 to pin 5
  servo2.attach(SERVO_Y_PIN); // attach servo 2 to pin 6

  *x_angle=0;
  *y_angle=0;

  while(*y_angle < 90){
    Y_moveUp(y_angle);
    delay(100);
  }
}

void X_moveClockwise(int* x){
  servo1.write(SPEED_ANTICLOCKWISE);
  delay(42);
  
  servo1.write(STOP);
  *x += 10;
  if(*x == 360){
    *x = 0;
  }
  delay(100);
}

void X_moveAnticlockwise(int* x){
  servo1.write(SPEED_CLOCKWISE);
  delay(44);

  servo1.write(STOP);
  *x -= 10;
  if(*x == -360){
    *x = 0;
  }
  delay(100);
}

void Y_moveDown(int* y){
    if(*y >= 10){
    servo2.write(SPEED_CLOCKWISE);
    delay(35);
    servo2.write(STOP);
    *y -= 10;
    delay(100);
  }
}

void Y_moveUp(int* y){
    if(*y <= 80){
    servo2.write(SPEED_ANTICLOCKWISE);
    delay(45);
    servo2.write(STOP);
    *y += 10;
    delay(100);
  }
}