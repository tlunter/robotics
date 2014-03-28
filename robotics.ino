#include "motor.h"
#include "robot.h"

//#define LINE_FOLLOWER
//#define WALL_FOLLOWER
#define ROBOT_FOLLOWER

#if defined(LINE_FOLLOWER)
#include "led_array.h"
#include "line_follower_robot.h"
#endif

#if defined(WALL_FOLLOWER) || defined(ROBOT_FOLLOWER)
#include "sodar.h"
#endif

#if defined(WALL_FOLLOWER)
#include "wall_follower_robot.h"
#endif

#if defined(ROBOT_FOLLOWER)
#include "robot_follower_robot.h"
#endif

Motor *a;
Motor *b;
Robot *robot;
#if defined(LINE_FOLLOWER)
LedArray *ledArray;
#endif

#if defined(WALL_FOLLOWER) || defined(ROBOT_FOLLOWER)
Sodar *sodarOne;
Sodar *sodarTwo;
#endif

void setup(void)
{
    Serial.begin(9600);
  
    a = new Motor(12, 3, 9, A0);
    b = new Motor(13, 11, 8, A1);
  
    robot = new Robot(a, b);
#if defined(LINE_FOLLOWER)
    ledArray = new LedArray(A2);
    delay(1000);
    ledArray->init();
#endif
#if defined(WALL_FOLLOWER) || defined(ROBOT_FOLLOWER)
    sodarOne = new Sodar(50, 51);
    sodarTwo = new Sodar(52, 53);
    sodarOne->init();
    sodarTwo->init();
#endif
}

void loop(void)
{
#if defined(LINE_FOLLOWER)
    LineFollowerRobotLoop(robot, ledArray);
#elif defined(WALL_FOLLOWER)
    WallFollowerRobotLoop(robot, sodarOne, sodarTwo);
#elif defined(ROBOT_FOLLOWER)
    RobotFollowerRobotLoop(robot, sodarOne, sodarTwo);
#endif
    delay(50);
}
