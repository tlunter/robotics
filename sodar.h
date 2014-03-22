#ifndef __SODAR
#define __SODAR

class Sodar {
    public:
        int triggerPin;
        int echoPin;
        unsigned long duration;
        Sodar(int, int);
        void init();
        unsigned long distance();
        unsigned long microsecondsToCentimeters(unsigned long);

};

#endif
