#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "sodar.h"
#include "sodar_robot.h"

#define SODARDEBUG 1

void SodarRobotLoop(Robot *robot, Sodar *sodarFront, Sodar *sodarSide)
{
	double frontDistance;
	double sideDistance;

	frontDistance = sodarFront->distance();
	sideDistance  = sodarSide->distance();

	#ifdef SODARDEBUG
	Serial.println("");
    Serial.print("Front: ");
    Serial.print(frontDistance);
    Serial.print(" cm");
    Serial.print("      Side: ");
    Serial.print(sideDistance);
    Serial.print(" cm");
    #endif

    // Make sure the front sonar is not triggering
    if (frontDistance < 12)
    {
    	robot->turn_left();
    	return;
    }

    // manage distance from wall
    if (sideDistance <= 10 && sideDistance >= 5)
    {
    	robot->forward();
    	return;
    }

    if (sideDistance < 5)
    {
    	robot->slight_left();
    	return;
    }

    if (sideDistance > 10)
    {
    	robot->slight_right();
    	return;
    }

}