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
enemy_robot_distance_t currentDistance;
enemy_robot_angle_t currentAngle;

void RobotFollowerRobotLoop(Robot *robot, Sodar *sodarLeft, Sodar *sodarCenter, Sodar *sodarRight)
{
    // First, get left/right/center val. for now, center
    currentAngle = ROBOT_ANGLE_CENTER;

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
        currentDistance = ROBOT_DIR_CLOSE;
    }
    else if (fbDistance < MAX_THRESHOLD && fbDistance > MAX_DISTANCE)
    {
        Serial.print("Too far\t");
        currentDistance = ROBOT_DIR_FAR;
    }
    else
    {
        // even if its past our MAX_THRESHOLD, we report its 'just right' so it stays put while it turns to find it
        Serial.print("Just right\t");
        currentDistance = ROBOT_DIR_OPTIMAL;
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
        robot->percentDrive(percentDistance);
    }

    Serial.println();
}
