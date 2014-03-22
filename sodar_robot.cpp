#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "sodar.h"
#include "sodar_robot.h"

void SodarRobotLoop(Robot *robot, Sodar *sodarFront, Sodar *sodarSide)
{
    Serial.print("Front: ");
    Serial.print(sodarFront->distance());
    Serial.println(" cm");
    Serial.print("Side: ");
    Serial.print(sodarSide->distance());
    Serial.println(" cm");
}