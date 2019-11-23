#include "scanstatus.h"

using namespace smartradar;

ScanStatus::ScanStatus() {
    alarm = false;
    clearMeasures();
}

bool ScanStatus::isAlarmActive() {
    return alarm;
}

void ScanStatus::updateMeasure(Measure *measure) {
    if (measure->sliceIdx < 0 || measure->sliceIdx >= SCAN_SLICES) {
        return;
    }

    Measure *m = &measures[measure->sliceIdx];
    m->angle = measure->angle;
    m->distance = measure->distance;
}

Measure* ScanStatus::getMeasures() {
    return measures;
}

void ScanStatus::clearMeasures() {
    for (int i = 0; i < SCAN_SLICES; i++) {
        measures[i].sliceIdx = i;
        measures[i].distance = 0.0;
        measures[i].angle = 0;
    }
}

void ScanStatus::setAlarm(bool state) {
    alarm = state;
}

int ScanStatus::getCurrentSlice() {
    return currentSlice;
}

void ScanStatus::setCurrentSlice(int slice) {
    currentSlice = slice;
}

int ScanStatus::getScanDuration() {
    return scanDuration;
}

void ScanStatus::setScanDuration(int duration) {
    scanDuration = duration;
}


RadarMode ScanStatus::getCurrentMode() {
    return currentMode;
}

void ScanStatus::setCurrentMode(RadarMode mode) {
    currentMode = mode;
}
