#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "sodar.h"
#include "sodar_robot.h"

void SodarRobotLoop(Robot *robot, Sodar *sodarFront, Sodar *sodarSide)
{
	Serial.println("");
    Serial.print("Front: ");
    Serial.print(sodarFront->distance());
    Serial.print(" cm");
    Serial.print("      Side: ");
    Serial.print(sodarSide->distance());
    Serial.print(" cm");
}