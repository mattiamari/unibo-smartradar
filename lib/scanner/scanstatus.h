#ifndef SMARTRADAR_SCANSTATUS_H
#define SMARTRADAR_SCANSTATUS_H

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
    private:
        Measure measures[SCAN_SLICES];
        bool alarm;
    };
}

#endif