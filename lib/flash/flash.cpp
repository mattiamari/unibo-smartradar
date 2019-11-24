#include "flash.h"

using namespace smartradar;

Flash::Flash(Led *led, ScanStatus *scanStatus) {
    this->led = led;
    this->scanStatus = scanStatus;
}

void Flash::step() {
    if (scanStatus->hasDetectedInCurrentSlice() && !led->isOn()) {
        led->turnOn();
        return;
    }

    if (led->isOn()) {
        scanStatus->setDetectedInCurrentSlice(false);
        led->turnOff();
    }
}

bool Flash::isComplete() {
    return false;
}

TaskType Flash::getType() {
    return TASK_FLASH;
}
