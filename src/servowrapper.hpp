#pragma once

#include <Servo.h>

class ServoWrapper {
private:
    Servo servo;
    int pin;
    int limMin;
    int limMax;
    int degMin;
    int degMax;
    unsigned long speed;
    
    int lastKnownPos = 0;
    int target = 0;
    unsigned long lastSetTime = 0;
    unsigned long expectedDuration = 0;
public:
    ServoWrapper(int pin, int limMin = 0, int limMax = 180, int degMin = 0, int degMax = 180, unsigned long speed = 500);

    void setEnabled(bool enabled);
    bool getEnabled();
    inline void setRaw(int angleRaw);
    void set(int angle);
    void resetTo(int angle);
    int getApproxAngle();
};
