#include <Servo.h>

class ServoWrapper {
private:
    Servo servo;
    int pin;
    int limMin;
    int limMax;
    int degMin;
    int degMax;
    long speed;
public:
    ServoWrapper(int pin, int limMin = 0, int limMax = 180, int degMin = 0, int degMax = 180, long speed = 500000);
    void setEnabled(bool enabled);
    bool getEnabled();
    void setRaw(int angleRaw);
    void set(int angle);
};
