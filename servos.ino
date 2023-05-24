#include <Servo.h>

Servo servo1;
Servo servo2;

void servos_init() {
  servo1.attach(SERVO_X_PIN); // attach servo 1 to pin 9
  servo2.attach(SERVO_Y_PIN); // attach servo 2 to pin 10
}

void servos_set(int servo_x_angle, int servo_y_angle){
  servo1.write(servo_x_angle);
  servo2.write(servo_y_angle);
}