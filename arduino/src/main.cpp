#include "headers.hpp"
#include "servowrapper.hpp"
#include "spinstance.hpp"
#include "button.hpp"


const float SQRT_2 = sqrt(2);
const float INV_SQRT_2 = 1 / SQRT_2;

ServoWrapper base(PIN_SERVO_BASE, LIMIT_BASE_MIN, LIMIT_BASE_MAX, 0, 90);
ServoWrapper vertical(PIN_SERVO_VERTICAL, LIMIT_VERT_MIN, LIMIT_VERT_MAX, 0, 90);
Spinstance spinstance(&base, &vertical);

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

        spinstance.setDirection(-1);
        spinstance.move(40, 1.25 * PI);
        delay(1000);

        spinstance.reset();
        while (digitalRead(PIN_RAPIDLY_WIPE_TASSEL)) {
            spinstance.update();
        }
        while (!spinstance.passedAngle(3 * PI / 2)) {
            spinstance.update();
        }
        spinstance.movePolar(90, 0);
        delay(200);

        base.setEnabled(false);
        vertical.setEnabled(false);
    }
}
