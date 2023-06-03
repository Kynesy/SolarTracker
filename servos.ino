/**
*   @file servos.ino
*
*   @brief Logica che gestisce il movimento del servomotori
*/

#include <Servo.h>

Servo servo1; /**< Classe del servomotore 1 - movimento lungo l'asse orizzontale*/
Servo servo2; /**< Classe del servomotore 2 - movimento lungo l'asse verticale*/

#define SPEED_CLOCKWISE 58
#define SPEED_ANTICLOCKWISE 122

#define STOP 90
#define PERIOD 1000
/**
*   @brief La funzione inizializza i servomotori
*
*   @note La funzione va richiamata nel setup
*/
void servos_init() {
  servo1.attach(SERVO_X_PIN); // attach servo 1 to pin 9
  servo2.attach(SERVO_Y_PIN); // attach servo 2 to pin 10
}

/**
*   @brief La funzione muove i servo dell'angolo specificato
*
*   @param servo_x_angle Indica l'angolo sull'asse orizzontale
*   @param servo_y_angle Indica l'angolo sull'asse verticale
*/
void servos_set(int servo_x_angle, int servo_y_angle){
  Serial.println("Updating servos position");
  int time1 = 0;
  int time2 = 0;
  if(servo_x_angle < 0){
    time1 = map(servo_x_angle, -180, 0, 500, 0);  
    servo1.write(SPEED_ANTICLOCKWISE);
    delay(time1);
  }
  if(servo_x_angle > 0){
    time1 = map(servo_x_angle, -180, 0, 500, 0);  
    servo1.write(SPEED_ANTICLOCKWISE);
    delay(time1);
  }
  servo1.write(STOP);
  servo2.write(servo_y_angle);
  servo2.write(STOP);
}