#include "servoimpl.h"

using namespace smartradar;

ServoImpl::ServoImpl(byte pin) {
    servo.attach(pin);
}

int ServoImpl::getAngle() {
    return servo.read();
}

void ServoImpl::setAngle(int angle){
    servo.write(angle);
}

int ServoImpl::getAngleMin() {
    return 0;
}

int ServoImpl::getAngleMax() {
    return 170;
}
