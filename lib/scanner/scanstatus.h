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
        bool hasDetectedInCurrentSlice();
        void updateMeasure(Measure *measure);
        Measure *getMeasures();
        void clearMeasures();
        void setAlarm(bool state);
        void setDetectedInCurrentSlice(bool state);
        int getCurrentSlice();
        void setCurrentSlice(int slice);
        unsigned int getScanDuration();
        void setScanDuration(unsigned int duration);
        RadarMode getCurrentMode();
        void setCurrentMode(RadarMode mode);
    private:
        Measure measures[SCAN_SLICES];
        bool alarm;
        bool detectedInSlice;
        int currentSlice;
        unsigned int scanDuration;
        RadarMode currentMode;
    };
}

#endif
