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
#define SIDE_THRESHOLD 3.5

double centerDistance;
double leftDistance;
double rightDistance;

void RobotFollowerRobotLoop(Robot *robot, Sodar *sodarLeft, Sodar *sodarRight, Sodar *sodarCenter)
{
    leftDistance = sodarLeft->distance();
    delay(10);
    rightDistance  = sodarRight->distance();
    delay(10);
    centerDistance = sodarCenter->distance();

#if defined(DEBUG)
    Serial.print("Left: ");
    Serial.print(leftDistance);
    Serial.print("\tCenter: ");
    Serial.print(centerDistance);
    Serial.print("\tRight: ");
    Serial.println(rightDistance);
#endif
    if (centerDistance < MIN_DISTANCE)
    {
        //Robot is close to the left
        if ((abs(centerDistance - leftDistance) < SIDE_THRESHOLD || leftDistance > MAX_THRESHOLD) && (abs(centerDistance - rightDistance) < SIDE_THRESHOLD || rightDistance > MAX_THRESHOLD))
        {
            Serial.println("Back");
            robot->backward();
        }
        else if (leftDistance < rightDistance)
        { 
            Serial.println("Left and Back");
            robot->backward_slight_right();
        }
        else if (rightDistance < leftDistance)
        {
            Serial.println("Right and Back");
            robot->backward_slight_left();
        }
    }
    else if (centerDistance > MAX_DISTANCE && centerDistance < MAX_THRESHOLD)
    {
        if ((abs(centerDistance - leftDistance) < SIDE_THRESHOLD || leftDistance > MAX_THRESHOLD) && (abs(centerDistance - rightDistance) < SIDE_THRESHOLD || rightDistance > MAX_THRESHOLD))
        {
            Serial.println("Forward");
            robot->forward();
        }
        //Robot is far and left
        else if (leftDistance < rightDistance)
        {
            Serial.println("Left and Forward");
            robot->slight_left();
        }
        else if (rightDistance < leftDistance)
        {
            Serial.println("Right and Forward");
            robot->slight_right();
        }
    }
    else
    {
       if (leftDistance < MAX_DISTANCE)
       {
           robot->hard_left();
       }
       else if (rightDistance < MAX_DISTANCE)
       {
           robot->hard_right();
       }
       else
       {
           robot->stop();
       }
    }
}
