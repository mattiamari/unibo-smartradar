#include "mock_hw.h"

using namespace smartradar;

// Sonar
DummySonar::DummySonar() {
    reading = 0.0;
}

float DummySonar::getReading() {
    return reading;
}

float DummySonar::getDistanceMin() {
    return 0.5;
}

float DummySonar::getDistanceMax() {
    return 2.0;
}


// Servo
DummyServo::DummyServo() {
    angle = 0;
}

void DummyServo::setAngle(int angle) {
    this->angle = angle; 
}

int DummyServo::getAngle() {
    return angle;
}

int DummyServo::getAngleMin() {
    return 0;
}

int DummyServo::getAngleMax() {
    return 170;
}

// Led
DummyLed::DummyLed() {
    state = false;
}

bool DummyLed::isOn() {
    return state;
}

void DummyLed::turnOn() {
    state = true;
}

void DummyLed::turnOff() {
    state = false;
}

void DummyLed::toggle() {
    state = !state;
}