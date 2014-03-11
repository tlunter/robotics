#include "motor.h"
#include "robot.h"
#include "led_array.h"

Motor *a;
Motor *b;
Robot *robot;
LedArray *ledArray;
bool seenTape;

void setup(void)
{
  Serial.begin(9600);
  
  a = new Motor(12, 3, 9, A0);
  b = new Motor(13, 11, 8, A1);
  
  robot = new Robot(a, b);
  
  ledArray = new LedArray(A2);
  delay(1000);
  ledArray->init();

  seenTape = false;
}

void loop(void)
{
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
    break;

    case B01000:
    case B01100:
      Serial.println("Slight left");
      robot->slight_left();
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
      Serial.println("Slight right");
      robot->slight_right();
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
    break;

    default:
      if (seenTape)
      {
          Serial.println("Keep doing last");
          robot->stop();
      }
      else
      {
          Serial.println("Go");
          robot->forward();
      }
    break;
  }
  delay(50);
}
