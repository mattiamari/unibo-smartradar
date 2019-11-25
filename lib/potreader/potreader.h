#ifndef SMARTRADAR_POTREADER_H
#define SMARTRADAR_POTREADER_H

#include "task.h"
#include "potentiometer.h"
#include "scanstatus.h"

#define POT_CHANGE_THRESH 50

namespace smartradar
{
    class PotReader : public Task
    {
    public:
        PotReader(Potentiometer *pot, ScanStatus *scanStatus);
        void step();
        bool isComplete();
        TaskType getType();
    
    private:
        Potentiometer *pot;
        ScanStatus *scanStatus;
        int lastReading;
    };
}

#endif