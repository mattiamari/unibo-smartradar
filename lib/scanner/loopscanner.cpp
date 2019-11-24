#include "loopscanner.h"

using namespace smartradar;

LoopScanner::LoopScanner(Servo *servo, Sonar *sonar, Potentiometer *pot)
    : Scanner(servo, sonar, pot) {};

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
