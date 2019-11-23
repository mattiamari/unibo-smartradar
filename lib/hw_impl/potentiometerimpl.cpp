#include "potentiometerimpl.h"

using namespace smartradar;

Potentiometer::Potentiometer(byte pin) {
    pin_ = pin;
}

int Potentiometer::getReading() {
    return analogRead(pin_); 
}
