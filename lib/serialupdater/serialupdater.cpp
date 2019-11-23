#include "serialupdater.h"
#include <radarmode.h>

#include <string.h>

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
            "\"scanDuration\":%d,"
            "\"currentSlice\":%d,"
            "\"measures\":[",
        modeString,
        scanStatus->isAlarmActive(),
        SCAN_SLICES,
        scanStatus->getScanDuration(),
        scanStatus->getCurrentSlice()
    );
    serial->print(buf);

    Measure *m = scanStatus->getMeasures();

    for (int i = 0; i < SCAN_SLICES; i++) {
        sprintf(buf,
            "{\"i\":%d,\"a\":%d,\"d\":%.4f}",
            m[i].sliceIdx, m[i].angle, m[i].distance);
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
