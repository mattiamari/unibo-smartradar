#include "sonar.h"
#include "servo.h"
#include "led.h"

using namespace smartradar;

class DummySonar : public Sonar
{
public:
    float reading;

    DummySonar();
    float getReading();
    float getDistanceMin();
    float getDistanceMax();
};

class DummyServo : public Servo
{
public:
    int angle;

    DummyServo();
    void setAngle(int angle);
    int getAngle();
    int getAngleMin();
    int getAngleMax();
};

class DummyLed : public Led
{
public:
    bool state;

    DummyLed();
    bool isOn();
    void turnOn();
    void turnOff();
    void toggle();
};

class DummyPotentiometer : public Potentiometer
{
public:
    float reading;

    DummyPotentiometer();
    int getReading();
};
