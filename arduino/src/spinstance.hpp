#include <Arduino.h>

#include "servowrapper.hpp"

class Spinstance {
private:
    ServoWrapper* base;
    ServoWrapper* vert;
    float r;
    float a;
    float a0;
    float omega;
    unsigned long prevTime = 0;
public:
    Spinstance(ServoWrapper* base, ServoWrapper* vert);
    void reset();
    void movePolar(float degTheta, float degAsc);
    void move(float r, float a);
    void update();
    float getA();
    bool passedAngle(float a);
};
