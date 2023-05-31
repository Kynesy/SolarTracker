/**
*   @file servos.ino
*
*   @brief Logica che gestisce il movimento del servomotori
*/

#include <Servo.h>

Servo servo1; /**< Classe del servomotore 1 - movimento lungo l'asse orizzontale*/
Servo servo2; /**< Classe del servomotore 2 - movimento lungo l'asse verticale*/

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
  servo1.write(servo_x_angle);
  servo2.write(servo_y_angle);
}