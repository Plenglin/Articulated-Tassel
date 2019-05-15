#include <Arduino.h>
#include <servowrapper.hpp>

ServoWrapper::ServoWrapper(int pin, int limMin, int limMax, int degMin, int degMax, long speed) 
    : pin(pin), limMin(limMin), limMax(limMax), degMin(degMin), degMax(degMax), speed(speed) {
}

void ServoWrapper::setEnabled(bool enabled) {
    if (enabled) {
        servo.attach(pin);
    } else {
        servo.detach();
    }
}

bool ServoWrapper::getEnabled() {
    return servo.attached();
}

void ServoWrapper::setRaw(int angleRaw) {
    servo.write(angleRaw);
}

void ServoWrapper::set(int angle) {
    setRaw(map(angle, degMin, degMax, limMin, limMax));
}
