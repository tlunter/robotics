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
#define SIDE_THRESHOLD 4

#define ENEMY_HISTORY 40
#define POSSIBLE_DIR_MOVEMENT 2
#define POSSIBLE_ANGLE_MOVEMENT 3
#define NUM_CORRECT_TRACKING 2

double fbDistance; // forward-back distance
int historyIndex = 0;
int *robotSpeed;
enemy_robot_distance_t enemyDistance[ENEMY_HISTORY] = {ROBOT_DIR_OPTIMAL};
// enemy_robot_angle_t enemyAngle[ENEMY_HISTORY] = {ROBOT_CENTER};
enemy_robot_distance_t currentDistance;
enemy_robot_angle_t currentAngle;

void RobotFollowerRobotLoop(Robot *robot, Sodar *sodarLeft, Sodar *sodarCenter, Sodar *sodarRight)
{
    robot->forward();
    robot->turn_right();
    return;

    // First, get left/right/center val. for now, center
    currentAngle = ROBOT_CENTER;

    switch (currentAngle)
    {
        case ROBOT_LEFT:
        fbDistance = sodarLeft->distance();
        break;

        case ROBOT_CENTER:
        fbDistance = sodarCenter->distance();
        break;

        case ROBOT_RIGHT:
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


    int previousHistory = (historyIndex - 1) % ENEMY_HISTORY;
    enemy_robot_distance_t previousDistance = enemyDistance[previousHistory];
    // enemy_robot_angle_t previousAngle = enemyAngle[previousHistory];

    enemy_robot_distance_t newDistance = ROBOT_DIR_NONE;

    if (abs(previousDistance - currentDistance) < 2)
    {
        // Serial.print("Catching up/Running away\t");
        enemyDistance[historyIndex] = currentDistance;
        newDistance = enemyDistance[historyIndex];
    }
    else
    {
        // Keep repeating previous command
        // Serial.print("Rapid speed change?\t");
    }


    switch(currentAngle)
    {
        case ROBOT_LEFT:
        robotSpeed = robot->turn_left();
        break;

        case ROBOT_RIGHT:
        robotSpeed = robot->turn_right();
        break;

        case ROBOT_CENTER:
        
        break;
    }         
    free(robotSpeed);
    
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