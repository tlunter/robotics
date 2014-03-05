#include "motor.h"
#include "robot.h"

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
  ledArray = new LedArray(4);
}

void loop(void)
{
  switch(ledArray->isTape())
  {
    case B1000:
      robot->turn_left();
    break;

    case B1100:
      robot->slight_left();
    break;

    case B0110:
      robot->forward();
    break;

    case B0011:
      robot->slight_right();
    break;

    case B0001:
      robot->turn_right();
    break;
  }
}
