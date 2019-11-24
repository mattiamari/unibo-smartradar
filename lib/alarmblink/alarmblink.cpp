#include "alarmblink.h"

using namespace smartradar;

AlarmBlink::AlarmBlink(Led *led) : Blink(led) {}

void AlarmBlink::step() {
    if (!scanStatus->isAlarmActive()) {
        if (led->isOn()) {
            led->turnOff();
        }
        return;
    }

    Blink::step();
}

void AlarmBlink::setScanStatus(ScanStatus *scanStatus) {
    this->scanStatus = scanStatus;
}
