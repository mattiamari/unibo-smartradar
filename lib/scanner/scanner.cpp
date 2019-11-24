#include "scanner.h"
#include "scheduler.h"

using namespace smartradar;

int smartradar::sliceToAngle(int slice, int slicesCount, int min, int max) {
    return ((float)slice / slicesCount * (max - min)) + min + ((max - min) / slicesCount / 2);
}

Scanner::Scanner(Servo *servo, Sonar *sonar, Led *led) {
    this->servo = servo;
    this->sonar = sonar;
    this->led = led;
    scanStatus = nullptr;
    scanTime = 0;
    
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
    currentState = STATE_MEASURE;
}

void Scanner::stateMeasure() {
    float distance = sonar->getReading();

    scanStatus->getMeasures()[currentSlice].angle = currentAngle;
    scanStatus->getMeasures()[currentSlice].distance = distance;

    if (distance >= sonar->getDistanceMin() && distance <= sonar->getDistanceMax()) {
        scanStatus->setAlarm(true);
        detected = true;
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
    TASK_WAIT(elapsed, BLINK_DELAY_TICKS)

    led->turnOff();
    currentState = STATE_WAIT_NEXT;
}

void Scanner::stateWaitNext() {
    static unsigned int elapsed = 0;
    TASK_WAIT(elapsed, scanTime / TICK_INTERVAL_MS / SCAN_SLICES)

    currentState = STATE_SERVO_MOVEMENT;
    currentSlice += direction;
}