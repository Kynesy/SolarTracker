/**
*   @file servos.ino
*
*   @brief Logica che gestisce il movimento del servomotori
*/

#include <Servo.h>

Servo servo1; /**< Classe del servomotore 1 - movimento lungo l'asse orizzontale*/
Servo servo2; /**< Classe del servomotore 2 - movimento lungo l'asse verticale*/

#define SPEED_CLOCKWISE 70
#define SPEED_ANTICLOCKWISE 120

#define STOP 90
#define PERIOD 1080

int x_angle = 0;
int y_angle = 0;
/**
*   @brief La funzione inizializza i servomotori
*
*   @note La funzione va richiamata nel setup
*/
void servos_init() {
  servo1.attach(SERVO_X_PIN); // attach servo 1 to pin 5
  servo2.attach(SERVO_Y_PIN); // attach servo 2 to pin 6
}

/**
*   @brief La funzione muove i servo dell'angolo specificato
*
*   @param servo_x_angle Indica l'angolo sull'asse orizzontale
*   @param servo_y_angle Indica l'angolo sull'asse verticale
*/

void XmoveClockwise(){
  servo1.write(SPEED_CLOCKWISE);
  delay(45);
  servo1.write(STOP);
  x_angle += 10;
  if(x_angle == 360){
    x_angle = 0;
  }
  delay(100);
}

void XmoveAnticlockwise(){
  servo1.write(SPEED_ANTICLOCKWISE);
  delay(42);
  servo1.write(STOP);
  x_angle -= 10;
  if(x_angle == -360){
    x_angle = 0;
  }
  delay(100);
}

void Y_moveDown(){
    if(y_angle >= 10){
    servo2.write(SPEED_ANTICLOCKWISE);
    delay(40);
    servo2.write(STOP);
    y_angle -= 10;
    delay(100);
  }
}

void Y_moveUp(){
    if(y_angle <= 170){
    servo2.write(SPEED_CLOCKWISE);
    delay(47);
    servo2.write(STOP);
    y_angle += 10;
    delay(100);
  }
}