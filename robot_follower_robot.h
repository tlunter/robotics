#ifndef __ROBOT_FOLLOWER_ROBOT
#define __ROBOT_FOLLOWER_ROBOT

typedef enum {
    ROBOT_DIR_FORWARD,
    ROBOT_DIR_BACKWARD,
    ROBOT_DIR_STOP
} robot_direction_t;

typedef enum {
    ROBOT_TURN_LEFT,
    ROBOT_TURN_RIGHT,
    ROBOT_STRAIGHT
} robot_turn_t;

void RobotFollowerRobotLoop(Robot*, Sodar*, Sodar*, Sodar*);

#endif

