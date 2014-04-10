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
        void backward_slight_left();
        void backward_slight_right();
        void left(int);
        void right(int);

        void percentDrive(double);
    private:
        void drive(int*);
};

#endif
