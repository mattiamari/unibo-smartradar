#ifndef SMARTRADAR_ALARMBLINK_H
#define SMARTRADAR_ALARMBLINK_H

#include "blink.h"
#include "scanstatus.h"

namespace smartradar
{
    class AlarmBlink : public Blink
    {
    public:
        AlarmBlink(Led *led) : Blink(led) {};
        void step();
        void setScanStatus(ScanStatus *scanStatus);
    private:
        ScanStatus *scanStatus;
    };
}

#endif