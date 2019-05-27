#include <Arduino.h>

#include "headers.hpp"
#include "servowrapper.hpp"
#include "button.hpp"


const float SQRT_2 = sqrt(2);
const float INV_SQRT_2 = 1 / SQRT_2;

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

void movePolar(float r, float theta) {
    base.set((sin(theta) + 1) * r);
    vertical.set((cos(theta) + 1) * r);
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
        vertical.setEnabled(true);

        movePolar(1, 3.14);
        delay(1000);

        float theta = 3.14;
        float velocity = 20;
        unsigned long prevTime = millis();
        while (digitalRead(PIN_RAPIDLY_WIPE_TASSEL)) {
            unsigned long currTime = millis();
            float dt = (currTime - prevTime) / 1000.0;
            prevTime = currTime;

            //velocity = min(velocity + 10 * dt, 20.00);
            theta = (theta + dt * velocity);
            movePolar(theta);
        }

        base.setEnabled(false);
        vertical.setEnabled(false);
    }
}
