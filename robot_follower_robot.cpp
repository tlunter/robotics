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

#define ENEMY_HISTORY 40
#define POSSIBLE_DIR_MOVEMENT 2
#define POSSIBLE_ANGLE_MOVEMENT 3
#define NUM_CORRECT_TRACKING 2

double centerDistance;
double leftDistance;
double rightDistance;
int historyIndex = 0;
enemy_robot_distance_t enemyDistance[ENEMY_HISTORY] = {ROBOT_DIR_OPTIMAL};
enemy_robot_angle_t enemyAngle[ENEMY_HISTORY] = {ROBOT_CENTER};
enemy_robot_distance_t currentDistance;
enemy_robot_angle_t currentAngle;

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
        Serial.print("Too close\t");
        currentDistance = ROBOT_DIR_CLOSE;
    }
    else if (centerDistance < MAX_THRESHOLD && centerDistance > MAX_DISTANCE)
    {
        Serial.print("Too far\t");
        currentDistance = ROBOT_DIR_FAR;
    }
    else
    {
        Serial.print("Just right\t");
        currentDistance = ROBOT_DIR_OPTIMAL;
    }

    if (abs(leftDistance - rightDistance) < SIDE_THRESHOLD ||
        (leftDistance > MAX_THRESHOLD &&
         rightDistance > MAX_THRESHOLD &&
         centerDistance < MAX_THRESHOLD))
    {
        Serial.print("In Front\t");
        currentAngle = ROBOT_CENTER;
    }
    else if (abs(leftDistance - centerDistance) < SIDE_THRESHOLD &&
        abs(rightDistance - leftDistance) > SIDE_THRESHOLD &&
        abs(rightDistance - centerDistance) > SIDE_THRESHOLD)
    {
        Serial.print("Front left\t");
        currentAngle = ROBOT_LEFT_CENTER;
    }
    else if (abs(rightDistance - centerDistance) < SIDE_THRESHOLD &&
        abs(rightDistance - leftDistance) > SIDE_THRESHOLD &&
        abs(leftDistance - centerDistance) > SIDE_THRESHOLD)
    {
        Serial.print("Front right\t");
        currentAngle = ROBOT_RIGHT_CENTER;
    }
    else if (leftDistance < MAX_THRESHOLD &&
            (centerDistance - leftDistance) > SIDE_THRESHOLD &&
            (rightDistance - leftDistance) > SIDE_THRESHOLD)
    {
        Serial.print("Left\t");
        currentAngle = ROBOT_LEFT;
    }
    else if (rightDistance < MAX_THRESHOLD &&
            (centerDistance - rightDistance) > SIDE_THRESHOLD &&
            (leftDistance - rightDistance) > SIDE_THRESHOLD)
    {
        Serial.print("Right\t");
        currentAngle = ROBOT_RIGHT;
    }

    Serial.println();

    int previousHistory = (historyIndex - 1) % ENEMY_HISTORY;
    enemy_robot_distance_t previousDistance = enemyDistance[previousHistory];
    enemy_robot_angle_t previousAngle = enemyAngle[previousHistory];

    enemy_robot_distance_t newDistance = ROBOT_DIR_NONE;
    enemy_robot_angle_t newAngle = ROBOT_NONE;

    if (abs(previousDistance - currentDistance) < 2)
    {
        Serial.print("Catching up/Running away\t");
        enemyDistance[historyIndex] = currentDistance;
        newDistance = enemyDistance[historyIndex];
    }
    else
    {
        // Keep repeating previous command
        Serial.print("Rapid speed change?\t");
    }

    if (abs(previousAngle - currentAngle) < 3)
    {
        Serial.print("Robot is turning\t");
        enemyAngle[historyIndex] = currentAngle;
        newAngle = enemyAngle[historyIndex];
    }
    else
    {
        // Keep repeating previous command
        Serial.print("Rapid direction change?\t");
    }

    Serial.println();

    int seenCount = 0;
    int lastHistoryIndex = historyIndex - ENEMY_HISTORY;
    for (int i = historyIndex - 1; i > lastHistoryIndex; i--)
    {
        if (abs(enemyAngle[i % ENEMY_HISTORY] - newAngle) < POSSIBLE_ANGLE_MOVEMENT &&
            abs(enemyDistance[i % ENEMY_HISTORY] - newDistance < POSSIBLE_DIR_MOVEMENT))
        {
            seenCount++;
        }
    }

    if (seenCount >= NUM_CORRECT_TRACKING)
    {
        if (newDistance == ROBOT_DIR_FAR)
        {
            if (newAngle == ROBOT_LEFT)
            {
                robot->turn_left();
            }
            else if (newAngle == ROBOT_LEFT_CENTER)
            {
                robot->slight_left();
            }
            else if (newAngle == ROBOT_CENTER)
            {
                robot->forward();
            }
            else if (newAngle == ROBOT_RIGHT_CENTER)
            {
                robot->slight_right();
            }
            else if (newAngle == ROBOT_RIGHT)
            {
                robot->turn_right();
            }
        }
        else if (newDistance == ROBOT_DIR_OPTIMAL)
        {
            if (newAngle == ROBOT_LEFT)
            {
                robot->hard_left();
            }
            else if (newAngle == ROBOT_LEFT_CENTER)
            {
                robot->hard_left();
            }
            else if (newAngle == ROBOT_CENTER)
            {
                robot->stop();
            }
            else if (newAngle == ROBOT_RIGHT_CENTER)
            {
                robot->hard_right();
            }
            else if (newAngle == ROBOT_RIGHT)
            {
                robot->hard_right();
            }
        }
        else if (newDistance == ROBOT_DIR_CLOSE)
        {
            if (newAngle == ROBOT_LEFT)
            {
                robot->backward_slight_right();
            }
            else if (newAngle == ROBOT_LEFT_CENTER)
            {
                robot->backward_slight_right();
            }
            else if (newAngle == ROBOT_CENTER)
            {
                robot->backward();
            }
            else if (newAngle == ROBOT_RIGHT_CENTER)
            {
                robot->backward_slight_left();
            }
            else if (newAngle == ROBOT_RIGHT)
            {
                robot->backward_slight_left();
            }
        }
    }
}
