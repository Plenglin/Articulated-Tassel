#include "servowrapper.hpp"

#include <Arduino.h>


ServoWrapper::ServoWrapper(int pin, int limMin, int limMax, int degMin, int degMax, unsigned long speed) 
    : pin(pin), limMin(limMin), limMax(limMax), degMin(degMin), degMax(degMax), speed(speed) {
}

void ServoWrapper::setEnabled(bool enabled) {
    if (enabled) {
        servo.attach(pin);
    } else {
        servo.detach();
    }
}

void ServoWrapper::resetTo(int angle) {
    unsigned long currentTime = millis();
    lastSetTime = currentTime;
    expectedDuration = 0;
    lastKnownPos = angle;
    target = angle;
    setRaw(map(angle, degMin, degMax, limMin, limMax));
}

bool ServoWrapper::getEnabled() {
    return servo.attached();
}

inline void ServoWrapper::setRaw(int angleRaw) {
    servo.write(angleRaw);
}

void ServoWrapper::set(int angle) {
    unsigned long currentTime = millis();
    int appxAngle = getApproxAngle();

    expectedDuration = (angle - appxAngle) * 1000 / speed;
    lastSetTime = currentTime;
    lastKnownPos = appxAngle;
    target = angle;
    setRaw(map(angle, degMin, degMax, limMin, limMax));
}

int ServoWrapper::getApproxAngle() {
    unsigned long currentTime = millis();
    unsigned long delta = min(currentTime - lastSetTime, expectedDuration);
    return map(delta, 0, expectedDuration, lastKnownPos, target);
}
