#include "motor.h"
#include "robot.h"

#define FAST_SPEED 130
#define LOW_SPEED 90

Robot::Robot(Motor *motor_a, Motor *motor_b) : 
    a(motor_a), b(motor_b)
{
}

int* Robot::forward()
{
    int *speed = new int[2]();
    speed[0] = FAST_SPEED;
    speed[1] = FAST_SPEED;
    drive(speed);

    return speed;
}

int* Robot::backward()
{
    int *speed = new int[2]();
    speed[0] = -FAST_SPEED;
    speed[1] = -FAST_SPEED;
    drive(speed);

    return speed;
}

int* Robot::stop()
{
    int *speed = new int[2]();
    drive(speed);

    return speed;
}

int* Robot::hard_left()
{
    int *speed = new int[2]();
    speed[0] = FAST_SPEED;
    speed[1] = -80;
    drive(speed);

    return speed;
}

int* Robot::hard_right()
{
    int *speed = new int[2]();
    speed[0] = -80;
    speed[1] = FAST_SPEED;
    drive(speed);

    return speed;
}

int* Robot::turn_left()
{
    int *speed = new int[2]();
    speed[0] = FAST_SPEED;
    speed[1] = 0;
    drive(speed);

    return speed;
}

int* Robot::turn_right()
{
    int *speed = new int[2]();
    speed[0] = 0;
    speed[1] = FAST_SPEED;
    drive(speed);

    return speed;
}

int* Robot::slight_left()
{
    int *speed = new int[2]();
    speed[0] = FAST_SPEED;
    speed[1] = LOW_SPEED;
    drive(speed);

    return speed;
}

int* Robot::slight_right()
{
    int *speed = new int[2]();
    speed[0] = LOW_SPEED;
    speed[1] = FAST_SPEED;
    drive(speed);

    return speed;
}

int* Robot::backward_slight_left()
{
    int *speed = new int[2]();
    speed[0] = -FAST_SPEED;
    speed[1] = -LOW_SPEED;
    drive(speed);

    return speed;
}

int* Robot::backward_slight_right()
{
    int *speed = new int[2]();
    speed[0] = -LOW_SPEED;
    speed[1] = -FAST_SPEED;
    drive(speed);

    return speed;
}

int* Robot::left(int pwm)
{
    int *speed = new int[2]();
    speed[0] = FAST_SPEED;
    speed[1] = pwm;
    drive(speed);

    return speed;
}

int* Robot::right(int pwm)
{
    int *speed = new int[2]();
    speed[0] = pwm;
    speed[1] = FAST_SPEED;
    drive(speed);

    return speed;
}

void Robot::drive(int *speed)
{
    this->a->drive(speed[0]);
    this->b->drive(speed[1]);
}
