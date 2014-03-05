#include "motor.h"
#include "robot.h"

Robot::Robot(Motor *motor_a, Motor *motor_b) : 
    a(motor_a), b(motor_b) {
}

void Robot::forward() {
    this->a->drive(255);
    this->b->drive(255);
}

void Robot::backward() {
    this->a->drive(-255);
    this->b->drive(-255);
}

void Robot::turn_left() {
    this->a->drive(255);
    this->b->drive(-255);
}

void Robot::turn_right() {
    this->a->drive(-255);
    this->b->drive(255);
}

void Robot::slight_left() {
    this->a->drive(255);
    this->b->drive(180);
}

void Robot::slight_right() {
    this->a->drive(180);
    this->b->drive(255);
}
