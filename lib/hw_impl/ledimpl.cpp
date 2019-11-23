#include "ledimpl.h"

using namespace smartradar;

LedImpl::LedImpl(byte pin) {
    pin_ = pin;
    ledState = false;
    pinMode(pin_, OUTPUT);
}


bool LedImpl::isOn() {
    return ledState;
}

void LedImpl::turnOn() {
    digitalWrite(pin_, HIGH);
    ledState = true;
}

void LedImpl::turnOff() {
    digitalWrite(pin_, LOW);
    ledState = false;
}

void LedImpl::toggle() {
    if(isOn()) {
        turnOff();
        return;
    }
    turnOn();
}
