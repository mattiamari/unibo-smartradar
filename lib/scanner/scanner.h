#ifndef SMARTRADAR_SCANNER_H
#define SMARTRADAR_SCANNER_H

#include "task.h"
#include "servo.h"
#include "sonar.h"
#include "led.h"
#include "scanstatus.h"
#include "scheduler.h"

#define BLINK_DELAY_TICKS 50 / TICK_INTERVAL_MS

namespace smartradar
{
    int sliceToAngle(int slice, int sliceCount, int min, int max);

    class Scanner : public Task
    {   
    public:
        Scanner(Servo *servo, Sonar *sonar, Led *led);
        void setScanStatus(ScanStatus *status);
        void setScanTime(unsigned int milliseconds);
        void step();
        bool hasDetected();
        bool isComplete();
        TaskType getType();

    protected:
        Servo *servo;
        Sonar *sonar;
        Led *led;
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
        void stateMeasure();
        void stateLedOn();
        void stateLedOff();
        void stateWaitNext();
        unsigned int getNearestBoundIndex();

        enum ScannerStates {
            STATE_SERVO_MOVEMENT = 1,
            STATE_MEASURE,
            STATE_LED_ON,
            STATE_LED_OFF,
            STATE_WAIT_NEXT
        };
    };
}

#endif