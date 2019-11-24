#ifndef SMARTRADAR_FLASH_H
#define SMARTRADAR_FLASH_H

#include "task.h"
#include "led.h"
#include "scanstatus.h"

namespace smartradar
{
    class Flash : public Task
    {
    public:
        Flash(Led *led, ScanStatus *scanStatus);
        void step();
        bool isComplete();
        TaskType getType();

    private:
        Led *led;
        ScanStatus *scanStatus;
    };
}

#endif
