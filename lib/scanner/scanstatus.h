#ifndef SMARTRADAR_SCANSTATUS_H
#define SMARTRADAR_SCANSTATUS_H

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
    };
}

#endif