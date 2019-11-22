#include "loopscanner.h"

using namespace smartradar;

void LoopScanner::step() {
    if (scanComplete) {
        if (!detected) {
            scanStatus->setAlarm(false);
        }

        reset();
    }

    Scanner::step();
}