#ifndef SMARTRADAR_SCANNER_H
#define SMARTRADAR_SCANNER_H

#include "task.h"
#include "servo.h"
#include "sonar.h"
#include "potentiometer.h"
#include "scanstatus.h"

#define BLINK_DELAY_TICKS 50 / TICK_INTERVAL_MS

#define SCAN_DURATION_MIN 2000
#define SCAN_DURATION_MAX 10000

namespace smartradar
{
    int sliceToAngle(int slice, int sliceCount, int min, int max);

    class Scanner : public Task
    {
    public:
        Scanner(Servo *servo, Sonar *sonar, Potentiometer *potentiometer);
        void setScanStatus(ScanStatus *status);
        void setScanTime(unsigned int milliseconds);
        void step();
        bool hasDetected();
        bool isComplete();
        TaskType getType();

    protected:
        Servo *servo;
        Sonar *sonar;
        Potentiometer *potentiometer;
        ScanStatus *scanStatus;

        unsigned int scanTime;
        int currentSlice;
        int currentAngle;
        short currentState;
        short direction;
        bool scanComplete;
        bool detected;

        void reset();
        void stateServoMovement();
        void stateWaitBefore();
        void stateMeasure();
        void stateLedOn();
        void stateLedOff();
        unsigned int getNearestBoundIndex();

        enum ScannerStates {
            STATE_SERVO_MOVEMENT = 1,
            STATE_WAIT_BEFORE,
            STATE_MEASURE
        };
    };
}

#endif
