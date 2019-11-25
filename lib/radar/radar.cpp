#include "radar.h"

#include "scanner.h"
#include "loopscanner.h"
#include "alarmblink.h"

using namespace smartradar;

Radar::Radar(Serial *serial, Sonar *sonar, Pir *pir, Servo *servo, Potentiometer *pot, Led *led1, Led *led2)
    : serialUpdater(serial, &scanStatus), alarmBlink(led2), scanner(servo, sonar, pot),
      loopScanner(servo, sonar, pot), flashOnDetect(led1, &scanStatus)
{
    this->serial = serial;
    this->sonar = sonar;
    this->pir = pir;
    this->servo = servo;
    this->pot = pot;
    this->led1 = led1;
    this->led2 = led2;

    scanStatus = ScanStatus();
    scheduler = Scheduler();

    currentMode = MODE_NONE;

    alarmBlink.setScanStatus(&scanStatus);
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

    scheduler.add(&flashOnDetect);
    scheduler.add(&alarmBlink, 300 / TICK_INTERVAL_MS);
    scheduler.add(&serialUpdater, 1000 / TICK_INTERVAL_MS);
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

    scheduler.add(&flashOnDetect);
    scheduler.add(&serialUpdater, 1000 / TICK_INTERVAL_MS);
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

    loopScanner = LoopScanner(servo, sonar, pot);
    loopScanner.setScanStatus(&scanStatus);

    scheduler.add(&flashOnDetect);
    scheduler.add(&alarmBlink, 300 / TICK_INTERVAL_MS);
    scheduler.add(&serialUpdater, 1000 / TICK_INTERVAL_MS);
    scheduler.add(&loopScanner);
}

void Radar::servoLeft() {
    servoStep(-1);
}

void Radar::servoRight() {
    servoStep(1);
}

void Radar::servoStep(short direction) {
    if (scanStatus.getCurrentMode() != MODE_MANUAL) {
        return;
    }

    int currSlice = scanStatus.getCurrentSlice();
    currSlice += direction;

    if (currSlice >= SCAN_SLICES - 1 || currSlice <= 0) {
        return;
    }

    servo->setAngle(sliceToAngle(currSlice, SCAN_SLICES, servo->getAngleMin(), servo->getAngleMax()));
    scanStatus.setCurrentSlice(currSlice);
}

void Radar::setScanDuration(int duration) {
    scanStatus.setScanDuration(duration);
}

void Radar::pirTriggered() {
    if (currentMode != MODE_SINGLE) {
        return;
    }

    // Do not run a scan if one is already scheduled
    if (scheduler.hasOfType(TASK_SCANNER)) {
        return;
    }

    scanner = Scanner(servo, sonar, pot);
    scanner.setScanStatus(&scanStatus);

    scheduler.add(&scanner);
}

void Radar::tick() {
    scheduler.schedule();
}

RadarMode Radar::getCurrentMode() {
    return currentMode;
}
