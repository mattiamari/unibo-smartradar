#include "potreader.h"

#include "scanner.h"
#include <stdlib.h>

using namespace smartradar;

PotReader::PotReader(Potentiometer *pot, ScanStatus *scanStatus) {
    this->pot = pot;
    this->scanStatus = scanStatus;
    lastReading = 0;
}

void PotReader::step() {
    int potReading = pot->getReading();

    if (abs(potReading - lastReading) > POT_CHANGE_THRESH) {
        scanStatus->setScanDuration((potReading / 1024.0 * (SCAN_DURATION_MAX - SCAN_DURATION_MIN)) + SCAN_DURATION_MIN);
        lastReading = potReading;
    }
}

bool PotReader::isComplete() {
    return false;
}

TaskType PotReader::getType() {
    return TASK_GENERIC;
}
