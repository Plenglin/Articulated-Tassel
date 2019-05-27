#include <Arduino.h>

#include "headers.hpp"
#include "servowrapper.hpp"
#include "button.hpp"


ServoWrapper base(PIN_SERVO_BASE, LIMIT_BASE_MIN, LIMIT_BASE_MAX, 0, 90);
ServoWrapper vertical(PIN_SERVO_VERTICAL, LIMIT_VERT_MIN, LIMIT_VERT_MAX, 0, 90);

Button btnDelay(PIN_MOVE_TASSEL_FWD);

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
    btnDelay.setup();
    pinMode(PIN_RAPIDLY_WIPE_TASSEL, INPUT_PULLUP);
    pinMode(13, OUTPUT);

    resetServos();
}

void loop() {
    int btnDelayOutput = btnDelay.update();
    if (btnDelayOutput == RISING_EDGE || btnDelayOutput == FALLING_EDGE) {
        Serial.println("Triggered the forward button");
        delay(DELAY_MOVE_FWD);
        moveTasselToForward();
        delay(1000);
        base.setEnabled(false);
        vertical.setEnabled(false);
    }

    if (digitalRead(PIN_RAPIDLY_WIPE_TASSEL)) {
        base.setEnabled(true);
        bool state = false;
        while (digitalRead(PIN_RAPIDLY_WIPE_TASSEL)) {
            base.set(state ? 0 : 90);
            delay(DELAY_WIPE_TASSEL);
            state = !state;
        }
        base.setEnabled(false);
    }
}

