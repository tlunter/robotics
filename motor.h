#ifndef __MOTOR
#define __MOTOR

class Motor {
    public:
        int direction, pwm, brake, sensing;
        Motor(int, int, int, int);
        void drive(int);
};

#endif
