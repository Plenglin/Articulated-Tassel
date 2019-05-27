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

void movePolar(float theta, float asc) {
    float degTheta = degrees(theta);
    float degAsc = degrees(asc);
    Serial.print(degTheta);
    Serial.print(" ");
    Serial.println(degAsc);

    base.set(degTheta);
    vertical.set(degAsc);
}

void moveAss(float psi, float zeta) {
    // Convert from ass to cartesian
    float cp = cos(psi);
    float sp = sin(psi);
    float cz = cos(zeta);
    float sz = sin(zeta);

    float inv2cp = INV_SQRT_2 * cp;
    float inv2czsp = INV_SQRT_2 * cz * sp;

    float x = inv2cp - inv2czsp;
    float y = -sp * sz;
    float z = -inv2cp - inv2czsp;

    float theta = atan2(y, x) + PI / 4;
    float asc = PI - acos(z);

    movePolar(theta, asc);
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

        movePolar(PI / 2, 0);
        delay(1000);

        float zeta = 0;
        float phi = 1.3;
        float omega = 10;
        unsigned long prevTime = millis();

        while (digitalRead(PIN_RAPIDLY_WIPE_TASSEL)) {
            unsigned long currTime = millis();
            float dt = (currTime - prevTime) / 1000.0;
            prevTime = currTime;

            omega = min(omega + 5 * dt, 20);
            phi = max(phi - 0.05 * dt, 0.5);
            zeta = (zeta + omega * dt);
            moveAss(phi, zeta);
        }

        base.setEnabled(false);
        vertical.setEnabled(false);
    }
}
