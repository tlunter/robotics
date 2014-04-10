#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "sodar.h"
#include "robot_follower_robot.h"

#define DEBUG
#define MIN_DISTANCE 10
#define MAX_DISTANCE 20
#define OPTIMAL_DISTANCE ((MAX_DISTANCE + MIN_DISTANCE) / 2)
#define RANGE_DISTANCE (MAX_DISTANCE - MIN_DISTANCE)
#define MAX_THRESHOLD 60

double fbDistance;
int historyIndex = 0;
enemy_robot_angle_t currentAngle;

enemy_robot_angle_t getCurrentAngle()
{
    enemy_robot_angle_t angle = ROBOT_ANGLE_NONE;
    unsigned char data = 0x40;

    while (Serial.available())
    {
        data = (unsigned char)Serial.read();
    }

    switch (data) {
        case 0x40:
            angle = ROBOT_ANGLE_NONE;
            break;
        case 0x41:
            angle = ROBOT_ANGLE_LEFT;
            break;
        case 0x42:
            angle = ROBOT_ANGLE_CENTER;
            break;
        case 0x43:
            angle = ROBOT_ANGLE_RIGHT;
            break;
        default:
            break;
    }

    return angle;
}

void RobotFollowerRobotLoop(Robot *robot, Sodar *sodarLeft, Sodar *sodarCenter, Sodar *sodarRight)
{
    // First, get left/right/center val. for now, center
    currentAngle = getCurrentAngle();

    switch (currentAngle)
    {
        case ROBOT_ANGLE_LEFT:
            fbDistance = sodarLeft->distance();
            break;

        case ROBOT_ANGLE_CENTER:
            fbDistance = sodarCenter->distance();
            break;

        case ROBOT_ANGLE_RIGHT:
            fbDistance = sodarRight->distance();
            break;

        default:
            fbDistance = OPTIMAL_DISTANCE;
            break;
    }

#if defined(DEBUG)
    Serial.print("Sensor: ");
    Serial.print(currentAngle);
    Serial.print("\tDistance: ");
    Serial.print(fbDistance);
#endif

    if (fbDistance < MIN_DISTANCE)
    {
        Serial.print("Too close\t");
    }
    else if (fbDistance < MAX_THRESHOLD && fbDistance > MAX_DISTANCE)
    {
        Serial.print("Too far\t");
    }
    else
    {
        // even if its past our MAX_THRESHOLD, we report its 'just right' so it stays put while it turns to find it
        Serial.print("Just right\t");
    }

    if (fbDistance < MAX_THRESHOLD)
    {
        if (fbDistance > MAX_DISTANCE)
        {
            fbDistance = MAX_DISTANCE;
        }
        if (fbDistance < MIN_DISTANCE)
        {
            fbDistance = MIN_DISTANCE;
        }

        double percentDistance;
        percentDistance = (fbDistance - (float)OPTIMAL_DISTANCE) / ((float)RANGE_DISTANCE / 2.0);
        Serial.print("\tPD: ");
        Serial.print(percentDistance);

        if (currentAngle == ROBOT_ANGLE_LEFT)
        {
            robot->driveLeft();
        }
        else if (currentAngle == ROBOT_ANGLE_CENTER)
        {
            robot->percentDrive(percentDistance);
        }
        else if (currentAngle == ROBOT_ANGLE_RIGHT)
        {
            robot->driveRight();
        }
    }

    Serial.println();
}
