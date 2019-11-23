#ifndef SMARTRADAR_SERIALUPDATER_H
#define SMARTRADAR_SERIALUPDATER_H

#include "task.h"
#include "serial.h"
#include "scanstatus.h"

namespace smartradar
{
    class SerialUpdater : public Task
    {
    public:
        SerialUpdater(Serial *serial, ScanStatus *scanStatus);
        void step();
        bool isComplete();
    private:
        Serial *serial;
        ScanStatus *scanStatus;
    };
}

#endif