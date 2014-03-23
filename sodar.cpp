#include "Arduino.h"
#include "sodar.h"

Sodar::Sodar(int triggerPin, int echoPin) :
	triggerPin(triggerPin), echoPin(echoPin), duration(0) {}

void Sodar::init() {
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

unsigned long Sodar::distance()
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(triggerPin, LOW);

    // Time in microsends till pin goes HIGH
    // Round trip time from SODAR, to object, back to SODAR
    duration = pulseIn(echoPin, HIGH);
    return microsecondsToCentimeters(duration);
}

// speed of sound = 340 m/s
// 1/340 = s/m = 0.002941176
// 0.0029 * 10^6 = ms/m = 2941.176
// 2941.176 / 100 = ms/cm = 29.41
// Divide by two for distance out
unsigned long Sodar::microsecondsToCentimeters(unsigned long microseconds)
{
    return microseconds / 29.41 / 2;
}