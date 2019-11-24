#include "sonarimpl.h"

using namespace smartradar;

SonarImpl::SonarImpl(short trigPin, short echoPin) {
    trigPin_ = trigPin;
    echoPin_ = echoPin;
    pinMode(trigPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
}

float SonarImpl::getReading(){
    digitalWrite(trigPin_, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin_, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin_, LOW);

    long t = pulseIn(echoPin_, HIGH, 20000);

    return t / 2 * 0.0343 / 100;
}

float SonarImpl::getDistanceMin() {
    return 0.2;
}

float SonarImpl::getDistanceMax() {
    return 1.0;
}
