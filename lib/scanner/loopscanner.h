#ifndef SMARTRADAR_LOOPSCANNER_H
#define SMARTRADAR_LOOPSCANNER_H

#include "scanner.h"

namespace smartradar
{
    class LoopScanner : public Scanner
    {
    public:
        LoopScanner(Servo *servo, Sonar *sonar, Led *led)
            : Scanner(servo, sonar, led) {};
        void step();
        bool isComplete();
    };
}

#endif