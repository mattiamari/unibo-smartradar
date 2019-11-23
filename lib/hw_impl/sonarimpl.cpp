#include "sonarimpl.h"

using namespace smartradar;

SonarImpl::SonarImpl(byte trigPin, byte echoPin) {
    trigPin_ = trigPin;
    echoPin_ = echoPin;
    pinMode(trigPin_, OUTPUT);
    pinMode(echoPin_, INPUT);
}

float SonarImpl::getReading(){
    /* invio impulso */
    digitalWrite(trigPin_, LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin_, HIGH);
    delayMicroseconds(5);
    digitalWrite(trigPin_, LOW);
    
    /* ricevi l’eco */
    long tUS = pulseInLong(echoPin_, HIGH);
    Serial.println(tUS);

    double t = tUS / 1000.0 / 1000.0 / 2;
    double d = t*vs;
    return d;
}

float SonarImpl::getDistanceMin() {
    return 0.2;
}

float SonarImpl::getDistanceMax() {
    return 3.0;
}
