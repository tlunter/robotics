#include "motor.h"
#include "robot.h"

//#define LED_ROBOT
#define SODAR_ROBOT

#include "led_array.h"
#include "led_robot.h"
#include "sodar.h"
#include "sodar_robot.h"

Motor *a;
Motor *b;
Robot *robot;
#if defined(LED_ROBOT)
LedArray *ledArray;
#elif defined(SODAR_ROBOT)
Sodar *sodarFront;
Sodar *sodarSide;
#endif

void setup(void)
{
    Serial.begin(9600);
  
    a = new Motor(12, 3, 9, A0);
    b = new Motor(13, 11, 8, A1);
  
    robot = new Robot(a, b);
#if defined(LED_ROBOT)
    ledArray = new LedArray(A2);
    delay(1000);
    ledArray->init();
#elif defined(SODAR_ROBOT)
    sodarFront = new Sodar(50, 51);
    sodarSide = new Sodar(52, 53);
    sodarFront->init();
    sodarSide->init();
#endif
}

void loop(void)
{
#if defined(LED_ROBOT)
    LedRobotLoop(robot, ledArray);
#elif defined(SODAR_ROBOT)
    SodarRobotLoop(robot, sodarFront, sodarSide);
#endif
    delay(50);
}
