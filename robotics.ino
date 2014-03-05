#include "motor.h"
#include "robot.h"

Motor *a;
Motor *b;
Robot *robot;

void setup(void)
{
  Serial.begin(9600);
  
  a = new Motor(12, 3, 9, A0);
  b = new Motor(13, 11, 8, A1);
  robot = new Robot(a, b);
}

void loop(void)
{
  robot->forward();
  delay(3000);
  robot->backward();
  delay(3000);
  robot->turn_left();
  delay(3000);
  robot->turn_right();
  delay(3000);
  robot->slight_left();
  delay(3000);
  robot->slight_right();
  delay(3000);
}
