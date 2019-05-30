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

void movePolar(float degTheta, float degAsc) {
    Serial.print(degTheta);
    Serial.print(" ");
    Serial.println(degAsc);

    base.set(degTheta);
    vertical.set(degAsc);
}

void moveTransformed(float r, float a) {
    float theta = 1.3 * r * cos(a) + 45;
    float asc = r * sin(a) + 45;
    movePolar(theta, asc);
}

void setup() {
    Serial.begin(115200);
    btnDelay.setup();
    pinMode(PIN_RAPIDLY_WIPE_TASSEL, INPUT_PULLUP);
    pinMode(PIN_REVERSE_TASSEL_SPIN, INPUT_PULLUP);
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
        Serial.println("Rapidly wiping tassel");
        base.setEnabled(true);
        vertical.setEnabled(true);

        float r = 40;
        float a = PI / 4;
        float omega = 15;

        movePolar(0, 0);
        delay(1000);

        unsigned long prevTime = millis();

        while (digitalRead(PIN_RAPIDLY_WIPE_TASSEL)) {
            unsigned long currTime = millis();
            float dt = (currTime - prevTime) / 1000.0;
            prevTime = currTime;

            //r = max(r - 1 * dt, 20);
            //omega = min(omega + 5 * dt, 20);
            float da = -omega * dt;
            Serial.println(omega);

            a = a + da;
            moveTransformed(r, a);
        }

        base.setEnabled(false);
        vertical.setEnabled(false);
    }
}
