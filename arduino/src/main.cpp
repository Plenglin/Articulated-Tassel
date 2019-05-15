#include <Arduino.h>

#include "headers.hpp"
#include "servowrapper.hpp"


ServoWrapper base(PIN_SERVO_BASE, LIMIT_BASE_MIN, LIMIT_BASE_MAX, 0, 90);
ServoWrapper vertical(PIN_SERVO_VERTICAL, LIMIT_VERT_MIN, LIMIT_VERT_MAX, 0, 90);

void setup() {
    Serial.begin(115200);
    pinMode(PIN_BTN_DELAY, INPUT_PULLUP);
}

volatile bool beginDelay = false;

void loop() {
    if (beginDelay) {
        delay(DELAY_TIME);
        beginDelay = false;
    }
}

void onDelayBtnPush() {
    beginDelay = true;
}

void moveTasselDefault() {
    base.set(0);
    vertical.set(0);
}
