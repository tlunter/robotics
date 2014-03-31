#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "sodar.h"
#include "robot_follower_robot.h"

#define DEBUG
#define MIN_DISTANCE 10
#define MAX_DISTANCE 20
#define MAX_THRESHOLD 40
#define THRESHOLD 2

void RobotFollowerRobotLoop(Robot *robot, Sodar *sodarLeft, Sodar *sodarRight)
{
    double leftDistance;
    double rightDistance;
    leftDistance = sodarLeft->distance();
    rightDistance  = sodarRight->distance();

#if defined(DEBUG)
    Serial.print("Left: ");
    Serial.print(leftDistance);
    Serial.print("\tRight: ");
    Serial.println(rightDistance);
#endif
    if (leftDistance < MIN_DISTANCE || rightDistance < MIN_DISTANCE)
    {
        if (abs(leftDistance - rightDistance) < THRESHOLD)
        {
            // Enemy robot is too close
            Serial.println("Back");
            robot->backward();
        }
        else if ((leftDistance - rightDistance) > THRESHOLD)
        {
            // Enemy robot is too close and to the right
            Serial.println("Right + Back");
            robot->backward_slight_left();
        }
        else if ((rightDistance - leftDistance) > THRESHOLD)
        {
            // Enemy robot is too close and to the left
            Serial.println("Left + Back");
            robot->backward_slight_right();
        }
    }
    else if ((leftDistance > MAX_DISTANCE && leftDistance < MAX_THRESHOLD) || (rightDistance > MAX_DISTANCE && rightDistance < MAX_THRESHOLD))
    {
        if (abs(leftDistance - rightDistance) < THRESHOLD)
        {
            // Enemy robot is going out of range
            Serial.println("Forward");
            robot->forward();
        }
        else if ((leftDistance - rightDistance) > THRESHOLD)
        {
            // Enemy robot is going out of range to the right
            Serial.println("Right + Forward");
            robot->slight_right();
        }
        else if ((rightDistance - leftDistance) > THRESHOLD)
        {
            // Enemy robot is going out of range to the left
            Serial.println("Left + Forward");
            robot->slight_left();
        }
    }
    else if ((leftDistance > MIN_DISTANCE && leftDistance < MAX_DISTANCE) ||
            (rightDistance > MIN_DISTANCE && rightDistance < MAX_DISTANCE))
    {
        if (abs(leftDistance - rightDistance) < THRESHOLD)
        {
            // Enemy robot is right where we want him
            Serial.println("Stop");
            robot->stop();
        }
        else if ((leftDistance - rightDistance) > THRESHOLD)
        {
            // Enemy robot is in range but off to the right
            Serial.println("Right");
            robot->turn_right();
        }
        else if ((rightDistance - leftDistance) > THRESHOLD)
        {
            // Enemy robot is in range but off to the left
            Serial.println("Left");
            robot->turn_left();
        }
    }
}
