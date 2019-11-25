#ifndef SMARTRADAR_RADAR_H
#define SMARTRADAR_RADAR_H

#include "radarmode.h"
#include "scanstatus.h"
#include "scheduler.h"
#include "serialupdater.h"
#include "alarmblink.h"
#include "scanner.h"
#include "loopscanner.h"
#include "flash.h"

#include "sonar.h"
#include "pir.h"
#include "servo.h"
#include "potentiometer.h"
#include "led.h"
#include "serial.h"

namespace smartradar
{
    class Radar
    {
    public:
        Radar(Serial *serial, Sonar *sonar, Pir *pir, Servo *servo, Potentiometer *pot, Led *led1, Led *led2);
        void setModeManual();
        void setModeSingle();
        void setModeAuto();
        void servoLeft();
        void servoRight();
        void setScanDuration(int duration);
        void pirTriggered();
        void tick();
        RadarMode getCurrentMode();

    private:
        RadarMode currentMode;
        ScanStatus scanStatus;
        Scheduler scheduler;
        SerialUpdater serialUpdater;
        AlarmBlink alarmBlink;
        Scanner scanner;
        LoopScanner loopScanner;
        Flash flashOnDetect;

        Sonar *sonar;
        Pir *pir;
        Servo *servo;
        Potentiometer *pot;
        Led *led1;
        Led *led2;

        Serial *serial;

        void servoStep(short direction);
    };
}

#endif
