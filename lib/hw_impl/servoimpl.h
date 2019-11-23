#ifndef SMARTRADAR_SERVOIMPL_H
#define SMARTRADAR_SERVOIMPL_H

#include "servo.h"

#include <Arduino.h>
#include <Servo.h>

namespace smartradar {
    class ServoImpl : public Servo {
    private:
        ::Servo servo;

    public:
        ServoImpl(byte pin);
        void setAngle(int angle);
        int getAngle();
        int getAngleMin();
        int getAngleMax();
    };
}

#endif
