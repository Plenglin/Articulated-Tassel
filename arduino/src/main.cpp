#include <Arduino.h>

#include "headers.hpp"
#include "servowrapper.hpp"


ServoWrapper base(PIN_SERVO_BASE, LIMIT_BASE_MIN, LIMIT_BASE_MAX, 0, 90);
ServoWrapper vertical(PIN_SERVO_VERTICAL, LIMIT_VERT_MIN, LIMIT_VERT_MAX, 0, 90);

volatile bool beginDelay = false;
volatile bool beginHelicopter = false;

void onDelayBtnPush() {
    beginDelay = true;
}

void onHelicopterBtnPush() {
    beginDelay = true;
}

void resetServos() {
    Serial.println("Resetting servos");
    
    base.setEnabled(true);
    base.resetTo(0);
    vertical.setEnabled(true);
    vertical.resetTo(0);
    delay(500);
    base.setEnabled(false);
    vertical.setEnabled(false);
}

void moveTasselToForward() {
    base.setEnabled(true);
    base.set(90);

    vertical.setEnabled(true);    
    vertical.set(0);
}

void moveTasselToHelicopter() {
    base.setEnabled(true);
    base.set(90);

    vertical.setEnabled(true);    
    vertical.set(90);
}

void setup() {
    Serial.begin(115200);

    pinMode(PIN_INPUT_0, INPUT_PULLUP);
    pinMode(PIN_INPUT_1, INPUT_PULLUP);
    pinMode(PIN_INPUT_2, INPUT_PULLUP);
    pinMode(13, OUTPUT);

    resetServos();
}

void loop() {
    if (beginDelay) {
        delay(DELAY_TIME);
        moveTasselToForward();
        delay(1000);
        beginDelay = false;
    }

    if (beginHelicopter) {
        moveTasselToHelicopter();
        delay(250);
        //analogWrite(PIN_MOTOR, 255);
        beginHelicopter = false;
    }
}

