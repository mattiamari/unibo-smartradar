#include "scanner.h"
#include "scheduler.h"

#define BLINK_DELAY 40 / TICK_INTERVAL_MS

using namespace smartradar;

int smartradar::sliceToAngle(int slice, int min, int max) {
    return (slice / SCAN_SLICES * (max - min)) + min;
}

Scanner::Scanner(Servo *servo, Sonar *sonar, Led *led) {
    this->servo = servo;
    this->sonar = sonar;
    this->led = led;
    scanStatus = nullptr;
    scanTime = 0;
    currentState = STATE_SERVO_MOVEMENT;
    scanComplete = false;
    currentSlice = getNearestSliceBound();
}

void Scanner::setScanStatus(ScanStatus *status) {
    scanStatus = status;
}

void Scanner::setScanTime(unsigned int milliseconds) {
    scanTime = milliseconds;
}

void Scanner::step() {
    if (scanStatus == nullptr) {
        return;
    }

    switch (currentState) {
        case STATE_SERVO_MOVEMENT: stateServoMovement(); break;
        case STATE_MEASURE: stateMeasure(); break;
        case STATE_LED_ON: stateLedOn(); break;
        case STATE_LED_OFF: stateLedOff(); break;
        case STATE_WAIT_NEXT: stateWaitNext();
    }
}

bool Scanner::isComplete() {
    return scanComplete;
}

unsigned int Scanner::getNearestSliceBound() {
    int min = servo->getAngleMin();
    int max = servo->getAngleMax();

    return servo->getAngle() > min + ((max - min) / 2) ? SCAN_SLICES - 1 : 0;
}

void Scanner::stateServoMovement() {
    if (currentSlice >= SCAN_SLICES) {
        scanComplete = true;
        return;
    }

    currentAngle = sliceToAngle(currentSlice, servo->getAngleMin(), servo->getAngleMax());
    servo->setAngle(currentAngle);
    currentState = STATE_MEASURE;
}

void Scanner::stateMeasure() {
    float distance = sonar->getReading();

    scanStatus->getMeasures()[currentSlice].angle = currentAngle;
    scanStatus->getMeasures()[currentSlice].distance = distance;

    if (distance >= sonar->getDistanceMin() && distance <= sonar->getDistanceMax()) {
        currentState = STATE_LED_ON;
        return;
    }

    currentState = STATE_WAIT_NEXT;
}

void Scanner::stateLedOn() {
    led->turnOn();
    currentState = STATE_LED_OFF;
}

void Scanner::stateLedOff() {
    static unsigned int elapsed = 0;
    TASK_WAIT(elapsed, BLINK_DELAY)

    led->turnOff();
    currentState = STATE_WAIT_NEXT;
}

void Scanner::stateWaitNext() {
    static unsigned int elapsed = 0;
    TASK_WAIT(elapsed, scanTime / TICK_INTERVAL_MS / SCAN_SLICES)

    currentState = STATE_SERVO_MOVEMENT;
    currentSlice += 1;
}