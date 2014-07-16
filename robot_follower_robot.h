#ifndef __ROBOT_FOLLOWER_ROBOT
#define __ROBOT_FOLLOWER_ROBOT

typedef enum {
    ROBOT_DIR_NONE = -1,
    ROBOT_DIR_FAR = 0,
    ROBOT_DIR_OPTIMAL,
    ROBOT_DIR_CLOSE
} enemy_robot_distance_t;

typedef enum {
    ROBOT_ANGLE_NONE = -1,
    ROBOT_ANGLE_LEFT = 0,
    ROBOT_ANGLE_CENTER,
    ROBOT_ANGLE_RIGHT
} enemy_robot_angle_t;

void RobotFollowerRobotLoop(Robot*, Sodar*, Sodar*, Sodar*);

#endif

