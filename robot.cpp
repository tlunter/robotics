#include "motor.h"
#include "robot.h"

#define FAST_SPEED 130
#define LOW_SPEED 90

Robot::Robot(Motor *motor_a, Motor *motor_b) : 
    a(motor_a), b(motor_b) {
}

void Robot::forward() {
    this->a->drive(FAST_SPEED);
    this->b->drive(FAST_SPEED);
}

void Robot::backward() {
    this->a->drive(-FAST_SPEED);
    this->b->drive(-FAST_SPEED);
}

void Robot::stop() {
    this->a->drive(0);
    this->b->drive(0);
}

void Robot::hard_left() {
    this->a->drive(FAST_SPEED);
    this->b->drive(-50);
}

void Robot::hard_right() {
    this->a->drive(-50);
    this->b->drive(FAST_SPEED);
}

void Robot::turn_left() {
    this->a->drive(FAST_SPEED);
    this->b->drive(0);
}

void Robot::turn_right() {
    this->a->drive(0);
    this->b->drive(FAST_SPEED);
}

void Robot::slight_left() {
    this->a->drive(FAST_SPEED);
    this->b->drive(LOW_SPEED);
}

void Robot::slight_right() {
    this->a->drive(LOW_SPEED);
    this->b->drive(FAST_SPEED);
}

void Robot::slight_left(int pwm) {
    this->a->drive(FAST_SPEED);
    this->b->drive(pwm);
}

void Robot::slight_right(int pwm) {
    this->a->drive(pwm);
    this->b->drive(FAST_SPEED);
}
