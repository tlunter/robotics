#ifndef __ROBOT
#define __ROBOT

class Robot {
    public:
        Robot(Motor*, Motor*);
        Motor *a, *b;
        int* forward();
        int* backward();
        int* stop();
        int* hard_left();
        int* hard_right();
        int* turn_left();
        int* turn_right();
        int* slight_left();
        int* slight_right();
        int* backward_slight_left();
        int* backward_slight_right();
        int* left(int);
        int* right(int);

        void percentDrive(double);
    private:
        void drive(int*);
};

#endif
