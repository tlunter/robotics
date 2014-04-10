#include "Arduino.h"
#include "motor.h"
#include "robot.h"
#include "led_array.h"
#include "line_follower_robot.h"

void LineFollowerRobotLoop(Robot *robot, LedArray *ledArray)
{
    static bool seenTape = false;
    switch(ledArray->isTape())
      {
        case B10000:
        case B11000:
        case B10100:
        case B11100:
        case B10010:
        case B11010:
        case B10110:
        case B11110:
            Serial.println("Turning left");
            robot->turn_left();
            seenTape = true;

            // if far left LED is tripped, turn left until it un-trips
            while (ledArray->isTape() > 16) {
                robot->turn_left();
            }
        break;

        case B01000:
        case B01100:
            Serial.println("Turn left");
            robot->turn_left();
            seenTape = true;
        break;

        case B00100:
        case B01010:
        case B01110:
        case B11111:
            Serial.println("Forward");
            robot->forward();
            seenTape = true;
        break;

        case B00010:
        case B00110:
            Serial.println("Turn right");
            robot->turn_right();
            seenTape = true;
        break;

        case B00001:
        case B00011:
        case B00101:
        case B00111:
        case B01001:
        case B01011:
        case B01101:
        case B01111:
            Serial.println("Turning right");
            robot->turn_right();
            seenTape = true;

            // if far right LED is tripped, turn right until it un-trips
            while (ledArray->isTape() % 2) {
                robot->turn_right();
            }
        break;

        default:
            if (seenTape)
            {
                    Serial.println("Keep doing last");
                // robot->stop();
            }
            else
            {
                Serial.println("Go");
                robot->forward();
            }
        break;
    }
}
