#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "sodar.h"
#include "wall_follower_robot.h"

#define SODAR_DEBUG 1
#define HISTORY_SIZE 10

void WallFollowerRobotLoop(Robot *robot, Sodar *sodarFront, Sodar *sodarSide)
{
    static double *history = new double[HISTORY_SIZE]();
    static unsigned int historyIndex = 0;

    double frontDistance;
    double sideDistance;

    double currentTrajectory = 0;

    frontDistance = sodarFront->distance();
    sideDistance  = sodarSide->distance();

    history[historyIndex++ % HISTORY_SIZE] = sideDistance;

    if (historyIndex < 10)
    {
        return;
    }


    // Determine slope factor
    float averageSlope = 0;
    for (int i = historyIndex; i > (historyIndex - HISTORY_SIZE + 1); i--)
    {
        int j = i % HISTORY_SIZE; // current measurement
        int k = (i - 1) % HISTORY_SIZE; // previous measurement

        if (abs(history[j] - history[k]) > 1)
        {
            currentTrajectory = history[j] - history[k];
            break;
        }
    }


    #ifdef SODAR_DEBUG
    Serial.println("");
    Serial.print("Front: ");
    Serial.print(frontDistance);
    Serial.print(" cm");
    Serial.print("      Side: ");
    Serial.print(sideDistance);
    Serial.print(" cm");
    Serial.print("    Trajectory: ");
    Serial.print(currentTrajectory);
    #endif


    // Make sure the front sonar is not triggering
    if (frontDistance < 12)
    {
        robot->hard_left();
        return;
    }


    if (sideDistance < 5 && currentTrajectory <= 0)
    {
        robot->slight_left();
        return;
    }

    if (sideDistance > 10 && currentTrajectory >= 0)
    {
        robot->slight_right();
        return;
    }

    if (sideDistance > 10)
    {
        robot->right(45);
        return;
    }

    // manage distance from wall   
    robot->forward();
}
