#include "potentiometerimpl.h"

using namespace smartradar;

PotentiometerImpl::PotentiometerImpl(short pin) {
    ::Serial.println(pin_);
    pin_ = pin;
}

int PotentiometerImpl::getReading() {
    return analogRead(pin_);
}
