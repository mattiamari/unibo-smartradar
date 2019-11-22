#ifndef SMARTRADAR_BLINK_H
#define SMARTRADAR_BLINK_H

#include "task.h"
#include "scheduler.h"
#include "led.h"

namespace smartradar
{
    class Blink : public Task
    {
    public:
        Blink(Led *led);
    private:
        Led *led;

        void step();
        bool isComplete();
    };
}

#endif
