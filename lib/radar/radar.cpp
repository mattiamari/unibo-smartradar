#include "radar.h"

#include "serialupdater.h"
#include "scanner.h"
#include "loopscanner.h"

using namespace smartradar;

Radar::Radar(Serial *serial, Sonar *sonar, Pir *pir, Servo *servo, Led *led1, Led *led2) {
    this->serial = serial;
    this->sonar = sonar;
    this->pir = pir;
    this->servo = servo;
    this->led1 = led1;
    this->led2 = led2;

    currentMode = MODE_NONE;
    scheduler = Scheduler();
}

void Radar::setModeManual() {
    if (currentMode == MODE_MANUAL) {
        return;
    }
    currentMode = MODE_MANUAL;

    scanStatus = ScanStatus();
    SerialUpdater serialUpdater = SerialUpdater(serial, &scanStatus);

    scheduler.add(&serialUpdater, 500 / TICK_INTERVAL_MS);
}

void Radar::setModeSingle() {
    if (currentMode == MODE_SINGLE) {
        return;
    }
    currentMode = MODE_SINGLE;
}

void Radar::setModeAuto() {
    if (currentMode == MODE_AUTO) {
        return;
    }
    currentMode = MODE_AUTO;
}

void Radar::pirTriggered() {
    Scanner scanner = Scanner(servo, sonar, led1);
    scheduler.add(&scanner, 0);
}

void Radar::tick() {
    scheduler.schedule();
}