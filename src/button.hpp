#pragma once

#include <Arduino.h>

#define RISING_EDGE 0b10
#define FALLING_EDGE 0b01

class Button {
private:
    uint8_t status;
    int pin;
public:
    Button(int pin);
    void setup();
    uint8_t update();
};
