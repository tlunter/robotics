#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "sodar.h"
#include "robot_follower_robot.h"

void RobotFollowerRobotLoop(Robot *robot, Sodar *sodarLeft, Sodar *sodarRight)
{
    double leftDistance;
    double rightDistance;
    leftDistance = sodarLeft->distance();
    rightDistance  = sodarRight->distance();

    Serial.print("Left: ");
    Serial.print(leftDistance);
    Serial.print("\tRight: ");
    Serial.println(rightDistance);
}
