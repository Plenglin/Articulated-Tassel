#include "button.hpp"

#include <Arduino.h>

Button::Button(int pin) : pin(pin) {
    
}

void Button::setup() {
    pinMode(pin, INPUT_PULLUP);
    int val = digitalRead(pin);
    status = (val << 1) | val;
}

uint8_t Button::update() {
    status = ((status << 1) | digitalRead(pin)) & 3;
    return status;
}
