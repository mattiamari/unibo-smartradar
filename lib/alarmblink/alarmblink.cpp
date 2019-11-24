#include "alarmblink.h"

using namespace smartradar;

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