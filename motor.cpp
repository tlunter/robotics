#include "Arduino.h"
#include "motor.h"

#define MOTOR_ENABLE 1

Motor::Motor(int direction, int pwm, int brake, int sensing) :
    direction(direction), pwm(pwm), brake(brake), sensing(sensing) {

    pinMode(this->direction, OUTPUT);
    pinMode(this->brake, OUTPUT);
    digitalWrite(this->direction, LOW);
    digitalWrite(this->brake, LOW);
}

/* Simple forward / backward function for individual motor
 * Input: (int) pwm  ::  between -255 & +255
 */
void Motor::drive(int pwm) {
    bool dir = (pwm > 0) ? LOW : HIGH;
    digitalWrite(this->direction, dir);

    #if MOTOR_ENABLE
    analogWrite(this->pwm, abs(pwm));
    #endif
}
