#ifndef __ROBOT_FOLLOWER_ROBOT
#define __ROBOT_FOLLOWER_ROBOT

typedef enum {
    ROBOT_DIR_NONE = -1,
    ROBOT_DIR_FAR = 0,
    ROBOT_DIR_CLOSE,
    ROBOT_DIR_OPTIMAL
} enemy_robot_distance_t;

typedef enum {
    ROBOT_NONE = -1,
    ROBOT_LEFT = 0,
    ROBOT_LEFT_CENTER,
    ROBOT_CENTER,
    ROBOT_RIGHT_CENTER,
    ROBOT_RIGHT
} enemy_robot_angle_t;

void RobotFollowerRobotLoop(Robot*, Sodar*, Sodar*, Sodar*);

#endif

