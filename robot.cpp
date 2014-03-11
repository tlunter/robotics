#include "motor.h"
#include "robot.h"

#define FAST_SPEED 255
#define LOW_SPEED 180

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
