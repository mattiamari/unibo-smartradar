#include "blink.h"

using namespace smartradar;

Blink::Blink(Led *led) : led(led) {}

void Blink::step() {
    led->toggle();
}

bool Blink::isComplete() {
    return false;
}

TaskType Blink::getType() {
    return TASK_GENERIC;
}
