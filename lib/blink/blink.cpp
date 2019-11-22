#include "blink.h"

using namespace smartradar;

Blink::Blink(Led *led) {
    this->led = led;
}

void Blink::step() {
    led->toggle();
}

bool Blink::isComplete() {
    return false;
}