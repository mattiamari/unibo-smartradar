#include "loopscanner.h"

using namespace smartradar;

LoopScanner::LoopScanner(Servo *servo, Sonar *sonar)
    : Scanner(servo, sonar) {};

void LoopScanner::step() {
    if (scanComplete) {
        if (!detected) {
            scanStatus->setAlarm(false);
        }

        reset();
    }

    Scanner::step();
}

bool LoopScanner::isComplete() {
    return false;
}
