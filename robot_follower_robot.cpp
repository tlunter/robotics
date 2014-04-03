#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "sodar.h"
#include "robot_follower_robot.h"

#define DEBUG
#define MIN_DISTANCE 10
#define MAX_DISTANCE 20
#define MAX_THRESHOLD 40
#define THRESHOLD 1

void RobotFollowerRobotLoop(Robot *robot, Sodar *sodarLeft, Sodar *sodarRight, Sodar *sodarCenter)
{   double centerDistance;
    double leftDistance;
    double rightDistance;
    delay(10);
    leftDistance = sodarLeft->distance();
    delay(10);
    rightDistance  = sodarRight->distance();
    delay(10);
    centerDistance = sodarCenter->distance();

#if defined(DEBUG)
    Serial.print("Left: ");
    Serial.print(leftDistance);
    Serial.print("\tRight: ");
    Serial.println(rightDistance);
#endif
    if (centerDistance < MIN_DISTANCE) {
        //Robot is close to the left
        if (leftDistance < rightDistance && leftDistance < centerDistance) { 
            Serial.println("Left and Back");
            robot->backward_slight_right();
        }
        else if (rightDistance < leftDistance && rightDistance < centerDistance) {
            Serial.println("Right and Back");
            robot->backward_slight_left();
        } else {
            Serial.println("Back");
            robot->backward();

        }
    }
    else if (centerDistance > MAX_DISTANCE) {
        //Robot is far and left
        if (leftDistance < rightDistance && leftDistance < centerDistance) { 
            Serial.println("Left and Forward");
            robot->forward_slight_left();
        }
        else if (rightDistance < leftDistance && rightDistance < centerDistance) {
            Serial.println("Right and Forward");
            robot->forward_slight_right();
        } else {
            Serial.println("Forward");
            robot->forward();

        }
    } else {
       if (leftDistance < MAX_DISTANCE) {
           robot->hard_left();
       }
       else if (rightDistance < MAX_DISTANCE) {
           robot->hard_right();
       } else {
           robot->stop();
       }
    }
