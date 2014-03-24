#ifndef __ROBOT
#define __ROBOT

class Robot {
    public:
        Robot(Motor*, Motor*);
        Motor *a, *b;
        void forward();
        void backward();
        void stop();
        void hard_left();
        void hard_right();
        void turn_left();
        void turn_right();
        void slight_left();
        void slight_right();
        void slight_left(int);
        void slight_right(int);
};

#endif
