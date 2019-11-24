#ifndef SMARTRADAR_SCANSTATUS_H
#define SMARTRADAR_SCANSTATUS_H

#include "radarmode.h"

#define SCAN_SLICES 16

namespace smartradar
{
    typedef struct Measure_s {
        unsigned int sliceIdx;
        int angle;
        float distance;
    } Measure;

    class ScanStatus
    {
    public:
        ScanStatus();
        ~ScanStatus() {};
        bool isAlarmActive();
        void updateMeasure(Measure *measure);
        Measure *getMeasures();
        void clearMeasures();
        void setAlarm(bool state);
        int getCurrentSlice();
        void setCurrentSlice(int slice);
        int getScanDuration();
        void setScanDuration(int duration);
        RadarMode getCurrentMode();
        void setCurrentMode(RadarMode mode);
    private:
        Measure measures[SCAN_SLICES];
        bool alarm;
        int currentSlice;
        int scanDuration;
        RadarMode currentMode;
    };
}

#endif
