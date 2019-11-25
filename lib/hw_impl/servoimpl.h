#ifndef SMARTRADAR_SERVOIMPL_H
#define SMARTRADAR_SERVOIMPL_H

#include "servointerface.h"

#include <Arduino.h>
#include <Servo.h>

namespace smartradar {
    class ServoImpl : public Servo {
    private:
        ::Servo servo;

    public:
        ServoImpl(short pin);
        void setAngle(int angle);
        int getAngle();
        int getAngleMin();
        int getAngleMax();
    };
}

#endif
