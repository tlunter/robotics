#ifndef __LED_ARRAY
#define __LED_ARRAY

class LedArray {
    public:
        LedArray(int);
        LedArray(int, int, int, int);
        int sensors[4];
};

#endif
