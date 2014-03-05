#ifndef __LED_ARRAY
#define __LED_ARRAY

#define LED_SENSOR_COUNT 4
#define LED_SAMPLE_COUNT 10

// Factor multiplied by the sense value for testing against floor average
#define LED_TAPE_FACTOR 1.5

class LedArray {
    public:
        LedArray(int);
        LedArray(int, int, int, int);
        int sensor_pins[LED_SENSOR_COUNT];
        int floor_average[LED_SENSOR_COUNT];
        void init();
        int* sense();
        bool* isTape();
};

#endif
