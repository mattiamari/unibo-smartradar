#include "scanner.h"
#include "scheduler.h"

#include <stdlib.h>

using namespace smartradar;

int smartradar::sliceToAngle(int slice, int slicesCount, int min, int max) {
    return ((float)slice / slicesCount * (max - min)) + min + ((max - min) / slicesCount / 2);
}

Scanner::Scanner(Servo *servo, Sonar *sonar) {
    this->servo = servo;
    this->sonar = sonar;
    scanStatus = nullptr;

    reset();
}

void Scanner::reset() {
    currentState = STATE_SERVO_MOVEMENT;
    scanComplete = false;
    currentSlice = getNearestBoundIndex();
    direction = 1;
    detected = false;

    // If starting from the right bound we should move backwards
    if (currentSlice == SCAN_SLICES - 1) {
        direction = -1;
    }
}

void Scanner::setScanStatus(ScanStatus *status) {
    scanStatus = status;
}

void Scanner::step() {
    if (scanStatus == nullptr) {
        return;
    }

    switch (currentState) {
        case STATE_SERVO_MOVEMENT: stateServoMovement(); break;
        case STATE_WAIT_BEFORE: stateWaitBefore(); break;
        case STATE_MEASURE: stateMeasure();
    }
}

bool Scanner::hasDetected() {
    return detected;
}

bool Scanner::isComplete() {
    return scanComplete;
}

TaskType Scanner::getType() {
    return TASK_SCANNER;
}

unsigned int Scanner::getNearestBoundIndex() {
    int min = servo->getAngleMin();
    int max = servo->getAngleMax();

    return servo->getAngle() > min + ((max - min) / 2) ? SCAN_SLICES - 1 : 0;
}

void Scanner::stateServoMovement() {
    if (currentSlice < 0 || currentSlice >= SCAN_SLICES) {
        scanComplete = true;
        return;
    }

    currentAngle = sliceToAngle(currentSlice, SCAN_SLICES, servo->getAngleMin(), servo->getAngleMax());
    servo->setAngle(currentAngle);

    scanStatus->setCurrentSlice(currentSlice);
    currentState = STATE_WAIT_BEFORE;
}

void Scanner::stateWaitBefore() {
    static unsigned int elapsed = 0;
    // The "-3" is there to account for the ticks taken by the state machine itself
    TASK_WAIT(elapsed, (scanStatus->getScanDuration() / TICK_INTERVAL_MS / SCAN_SLICES) - 3)

    currentState = STATE_MEASURE;
}

void Scanner::stateMeasure() {
    float distance = sonar->getReading();

    scanStatus->getMeasures()[currentSlice].angle = currentAngle;
    scanStatus->getMeasures()[currentSlice].distance = distance;

    scanStatus->setDetectedInCurrentSlice(false);

    if (distance >= sonar->getDistanceMin() && distance <= sonar->getDistanceMax()) {
        scanStatus->setAlarm(true);
        scanStatus->setDetectedInCurrentSlice(true);
        detected = true;
    }

    currentState = STATE_SERVO_MOVEMENT;
    currentSlice += direction;
}
