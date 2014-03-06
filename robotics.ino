#include "motor.h"
#include "robot.h"
#include "led_array.h"

Motor *a;
Motor *b;
Robot *robot;
LedArray *ledArray;

void setup(void)
{
  Serial.begin(9600);
  
  a = new Motor(12, 3, 9, A0);
  b = new Motor(13, 11, 8, A1);
  
  robot = new Robot(a, b);
  
  ledArray = new LedArray(A2);
  delay(1000);
  ledArray->init();
}

void loop(void)
{
  switch(ledArray->isTape())
  {
    case B1000:
      Serial.println("Turning left");
      robot->turn_left();
    break;

    case B1100:
      Serial.println("Slight left");
      robot->slight_left();
    break;

    case B0110:
      Serial.println("Forward");
      robot->forward();
    break;

    case B0011:
      Serial.println("Slight right");
      robot->slight_right();
    break;

    case B0001:
      Serial.println("Turning right");
      robot->turn_right();
    break;

    default:
      Serial.println("Stop");
      robot->stop();
    break;
  }
  delay(50);
}
