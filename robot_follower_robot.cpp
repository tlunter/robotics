#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "sodar.h"
#include "robot_follower_robot.h"

#define DEBUG
#define MIN_DISTANCE 10
#define MAX_DISTANCE 20
#define MAX_THRESHOLD 60
#define SIDE_THRESHOLD 4

double centerDistance;
double leftDistance;
double rightDistance;
robot_direction_t lineDirection;
robot_turn_t turnDirection;

void RobotFollowerRobotLoop(Robot *robot, Sodar *sodarLeft, Sodar *sodarCenter, Sodar *sodarRight)
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
        Serial.print("Backward\t");
        lineDirection = ROBOT_DIR_BACKWARD;
    }
    else if (centerDistance < MAX_THRESHOLD && centerDistance > MAX_DISTANCE)
    {
        Serial.print("Forward\t");
        lineDirection = ROBOT_DIR_FORWARD;
    }
    else
    {
        Serial.print("Stop\t");
        lineDirection = ROBOT_DIR_STOP;
    }

    if (centerDistance - leftDistance > SIDE_THRESHOLD && leftDistance < MAX_THRESHOLD)
    {
        Serial.print("Left\t");
        turnDirection = ROBOT_TURN_LEFT;
    }
    else if (centerDistance - rightDistance > SIDE_THRESHOLD && rightDistance < MAX_THRESHOLD)
    {
        Serial.print("Right\t");
        turnDirection = ROBOT_TURN_RIGHT;
    }
    else
    {
        Serial.print("Center\t");
        turnDirection = ROBOT_STRAIGHT;
    }
    Serial.println();

    if (lineDirection == ROBOT_DIR_FORWARD)
    {
    }
    else if (lineDirection == ROBOT_DIR_BACKWARD)
    {
    }
    else if (lineDirection == ROBOT_DIR_STOP)
    {
    }
}
