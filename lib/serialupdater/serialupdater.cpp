#include "serialupdater.h"
#include <radarmode.h>

#include <string.h>

#ifdef ARDUINO_UNO
    #include <Arduino.h>
#endif

using namespace smartradar;

SerialUpdater::SerialUpdater(Serial *serial, ScanStatus *scanStatus)
    : serial(serial), scanStatus(scanStatus) {}

void SerialUpdater::step() {
    char buf[128];
    const char *modeString;

    switch (scanStatus->getCurrentMode()) {
        case MODE_MANUAL: modeString = "m"; break;
        case MODE_SINGLE: modeString = "s"; break;
        case MODE_AUTO: modeString = "a"; break;
        default: modeString = "none";
    }

    sprintf(buf,
        "{"
            "\"m\":\"%s\","
            "\"a\":%d,"
            "\"s\":%d,"
            "\"sd\":%d,"
            "\"cs\":%d,"
            "\"me\":[",
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
        #ifdef ARDUINO_UNO
        dtostrf(m[i].distance, 2, 4, distanceString);
        sprintf(buf,
            "{\"i\":%d,\"a\":%d,\"d\":%s}",
            m[i].sliceIdx, m[i].angle, distanceString
        );
        #else
        sprintf(buf,
            "{\"i\":%d,\"a\":%d,\"d\":%f}",
            m[i].sliceIdx, m[i].angle, m[i].distance
        );
        #endif

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
