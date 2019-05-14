#define LOGLEVEL_INFO

#include <Arduino.h>
#include <Servo.h>

#define PIN_SERVO_BASE 10
#define PIN_SERVO_VERTICAL 11
#define PIN_MOTOR 3

#define PIN_BTN_DELAY 5

#define DELAY_TIME 5

/**
 * SG90 turning speed: 500 deg/s (.12s/60deg)
 */

Servo base;
Servo vertical;

void setup() {
  base.attach(PIN_SERVO_BASE);
  base.attach(PIN_SERVO_VERTICAL);

  pinMode(PIN_BTN_DELAY, INPUT_PULLUP);
}

volatile bool beginDelay = false;

void loop() {
  if (beginDelay) {
    delay(DELAY_TIME);
    
  }
}

void onDelayBtnPush() {
  beginDelay = true;
}
