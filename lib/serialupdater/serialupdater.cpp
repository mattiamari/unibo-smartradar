#include "serialupdater.h"

using namespace smartradar;

SerialUpdater::SerialUpdater(Serial *serial, ScanStatus *scanStatus) {
    this->serial = serial;
    this->scanStatus = scanStatus;
}

void SerialUpdater::step() {
    char buf[150];

    sprintf(buf,
        "{"
            "\"mode\": \"%s\","
            "\"alarm\": %d,"
            "\"slices\": %d,"
            "\"scanDuration\": %d,"
            "\"currentSlice\": %d,"
            "\"measures\": [",
        scanStatus->getCurrentMode(),
        scanStatus->isAlarmActive(),
        SCAN_SLICES,
        scanStatus->getCurrentSlice()
    );
    serial->print(buf);

    Measure *m = scanStatus->getMeasures();

    for (int i = 0; i < SCAN_SLICES; i++) {
        sprintf(buf,
            "{\"id\": %d, \"angle\": %d, \"distance\": %f}",
            m[i].sliceIdx, m[i].angle, m[i].distance);
        serial->print(buf);

        // Print trailing comma except for last element
        if (i < SCAN_SLICES - 1) {
            serial->print(",");
        }
    }

    serial->println("] }");

}

bool SerialUpdater::isComplete() {
    return false;
}
