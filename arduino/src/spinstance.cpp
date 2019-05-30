#include "spinstance.hpp"

#include <Arduino.h>


Spinstance::Spinstance(ServoWrapper *base, ServoWrapper *vert) : base(base), vert(vert) {

}

void Spinstance::reset() {
    prevTime = millis();
    r = 40;
    a = PI / 4;
    omega = 15;
}

void Spinstance::movePolar(float degTheta, float degAsc) {
    base->set(degTheta);
    vert->set(degAsc);
}

void Spinstance::move(float r, float a) {
    this->r = r;
    this->a = a;
    float theta = 1.3 * r * cos(a) + 45;
    float asc = r * sin(a) + 45;
    movePolar(theta, asc);
}

void Spinstance::update() {
    unsigned long currTime = millis();
    float dt = (currTime - prevTime) / 1000.0;
    prevTime = currTime;

    //r = max(r - 1 * dt, 20);
    //omega = min(omega + 5 * dt, 20);
    float da = -omega * dt;
    a0 = a;
    a += da;
    if (a < 0) {
        a += 2 * PI;
    } else if (a > 2 * PI) {
        a -= 2 * PI;
    }
    move(r, a);
}

bool Spinstance::passedAngle(float a) {
    float ap = this->a - a;
    float a0p = this->a0 - a;
    if (ap < 0) {
        ap += 2 * PI;
    }
    if (a0p < 0) {
        a0p += 2 * PI;
    }
    return ap > PI && a0p < PI;
}

float Spinstance::getA() {
    return a;
}
