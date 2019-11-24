#include "serialupdater.h"
#include <radarmode.h>

#include <string.h>

#ifdef ARDUINO_UNO
    #include <Arduino.h>
#endif

using namespace smartradar;

SerialUpdater::SerialUpdater(Serial *serial, ScanStatus *scanStatus) {
    this->serial = serial;
    this->scanStatus = scanStatus;
}

void SerialUpdater::step() {
    char buf[256];
    char modeString[8];

    switch (scanStatus->getCurrentMode()) {
        case MODE_MANUAL: strcpy(modeString, "manual"); break;
        case MODE_SINGLE: strcpy(modeString, "single"); break;
        case MODE_AUTO: strcpy(modeString, "auto"); break;
        default: strcpy(modeString, "none");
    }

    sprintf(buf,
        "{"
            "\"mode\":\"%s\","
            "\"alarm\":%d,"
            "\"slices\":%d,"
            "\"scanDur\":%d,"
            "\"currSlice\":%d,"
            "\"measures\":[",
        modeString,
        scanStatus->isAlarmActive(),
        SCAN_SLICES,
        scanStatus->getScanDuration(),
        scanStatus->getCurrentSlice()
    );
    serial->print(buf);

    Measure *m = scanStatus->getMeasures();
    char distanceString[8];

    for (int i = 0; i < SCAN_SLICES; i++) {
        dtostrf(m[i].distance, 2, 4, distanceString);
        sprintf(buf,
            "{\"i\":%d,\"a\":%d,\"d\":%s}",
            m[i].sliceIdx, m[i].angle, distanceString
        );
        serial->print(buf);

        // Print trailing comma except for last element
        if (i < SCAN_SLICES - 1) {
            serial->print(",");
        }
    }

    serial->print("]}\n");
}

bool SerialUpdater::isComplete() {
    return false;
}

TaskType SerialUpdater::getType() {
    return TASK_SERIALUPDATER;
}