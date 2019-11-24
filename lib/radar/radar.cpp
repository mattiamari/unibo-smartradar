#include "radar.h"

#include "scanner.h"
#include "loopscanner.h"
#include "alarmblink.h"

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
    scanStatus = ScanStatus();
    serialUpdater = new SerialUpdater(serial, &this->scanStatus);

    alarmBlink = new AlarmBlink(led2);
    alarmBlink->setScanStatus(&scanStatus);
}

void Radar::setModeManual() {
    if (currentMode == MODE_MANUAL) {
        return;
    }
    currentMode = MODE_MANUAL;
    scanStatus.setCurrentMode(MODE_MANUAL);

    scheduler.clear();
    led1->turnOff();
    led2->turnOff();
    scanStatus.setAlarm(false);

    scheduler.add(alarmBlink, 300 / TICK_INTERVAL_MS);
    scheduler.add(serialUpdater, 500 / TICK_INTERVAL_MS);
}

void Radar::setModeSingle() {
    if (currentMode == MODE_SINGLE) {
        return;
    }
    currentMode = MODE_SINGLE;
    scanStatus.setCurrentMode(MODE_SINGLE);

    scheduler.clear();
    led1->turnOff();
    led2->turnOff();
    scanStatus.setAlarm(false);

    scheduler.add(alarmBlink, 300 / TICK_INTERVAL_MS);
    scheduler.add(serialUpdater, 1000 / TICK_INTERVAL_MS);
}

void Radar::setModeAuto() {
    if (currentMode == MODE_AUTO) {
        return;
    }
    currentMode = MODE_AUTO;
    scanStatus.setCurrentMode(MODE_AUTO);

    scheduler.clear();
    led1->turnOff();
    led2->turnOff();
    scanStatus.setAlarm(false);

    LoopScanner *loopScanner = new LoopScanner(servo, sonar, led1);
    loopScanner->setScanStatus(&scanStatus);
    loopScanner->setScanTime(5000);

    scheduler.add(loopScanner, 0);
    scheduler.add(alarmBlink, 300 / TICK_INTERVAL_MS);
    scheduler.add(serialUpdater, 500 / TICK_INTERVAL_MS);
}

void Radar::pirTriggered() {
    if (currentMode != MODE_SINGLE) {
        return;
    }

    // Do not run a scan if one is already scheduled
    if (scheduler.hasOfType(TASK_SCANNER)) {
        return;
    }

    Scanner *scanner = new Scanner(servo, sonar, led1);
    scanner->setScanStatus(&scanStatus);
    scanner->setScanTime(6000);
    scheduler.add(scanner, 0);
}

void Radar::tick() {
    scheduler.schedule();
}

RadarMode Radar::getCurrentMode() {
    return currentMode;
}
