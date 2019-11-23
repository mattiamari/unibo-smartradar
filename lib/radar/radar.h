#ifndef SMARTRADAR_RADAR_H
#define SMARTRADAR_RADAR_H

#include "radarmode.h"
#include "scanstatus.h"
#include "scheduler.h"
#include "serialupdater.h"

#include "sonar.h"
#include "pir.h"
#include "servo.h"
#include "led.h"
#include "serial.h"

namespace smartradar
{
    class Radar
    {
    public:
        Radar(Serial *serial, Sonar *sonar, Pir *pir, Servo *servo, Led *led1, Led *led2);
        void setModeManual();
        void setModeSingle();
        void setModeAuto();
        void pirTriggered();
        void tick();
        RadarMode getCurrentMode();

    private:
        RadarMode currentMode;
        ScanStatus scanStatus;
        Scheduler scheduler;
        SerialUpdater serialUpdater;

        Sonar *sonar;
        Pir *pir;
        Servo *servo;
        Led *led1;
        Led *led2;

        Serial *serial;
    };
}

#endif
