#include <Arduino.h>
#include "led_array.h"

LedArray::LedArray(int pin) {
    for (int i = 0; i < LED_SENSOR_COUNT; i++) {
        this->sensor_pins[i] = pin+i;
    }
}

LedArray::LedArray(int pin1, int pin2, int pin3, int pin4) {
    this->sensor_pins[0] = pin1;
    this->sensor_pins[1] = pin2;
    this->sensor_pins[2] = pin3;
    this->sensor_pins[3] = pin4;
}

void LedArray::init() {
    for (int j = 0; j < LED_SAMPLE_COUNT; j++) {
        for (int i = 0; i < LED_SENSOR_COUNT; i++) {
            this->floor_average[i] += analogRead(sensor_pins[i]);
        }
    }

    for (int i = 0; i < LED_SENSOR_COUNT; i++) {
        this->floor_average[i] = this->floor_average[i] / LED_SAMPLE_COUNT;
    }
}

int* LedArray::sense() {
    int values[LED_SENSOR_COUNT] = {0};
    for (int i = 0; i < LED_SENSOR_COUNT; i++) {
        values[i] = analogRead(this->sensor_pins[i]);
    }
    return values;
}

char LedArray::isTape() {
    int *values = this->sense();

    char ret = 0;

    for (int i = 0; i < LED_SENSOR_COUNT; i++) {
        if (values[i] > (this->floor_average[i] * LED_TAPE_FACTOR)) {
            ret = (ret << 1) + 1;
        } else {
            ret = (ret << 1);
        }
    }

    return ret;
}
