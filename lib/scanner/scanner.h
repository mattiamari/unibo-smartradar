#ifndef SMARTRADAR_SCANNER_H
#define SMARTRADAR_SCANNER_H

#include "task.h"
#include "servo.h"
#include "sonar.h"
#include "led.h"
#include "scanstatus.h"

namespace smartradar
{
    int sliceToAngle(int slice, int min, int max);

    class Scanner : public Task
    {   
    public:
        Scanner(Servo *servo, Sonar *sonar, Led *led);
        void setScanStatus(ScanStatus *status);
        void setScanTime(unsigned int milliseconds);
        void step();
        bool isComplete();

    private:
        Servo *servo;
        Sonar *sonar;
        Led *led;
        ScanStatus *scanStatus;
        unsigned int scanTime;
        unsigned int currentSlice;
        int currentAngle;
        short currentState;
        bool scanComplete;

        void stateServoMovement();
        void stateMeasure();
        void stateLedOn();
        void stateLedOff();
        void stateWaitNext();
        unsigned int getNearestSliceBound();

        enum ScannerStates {
            STATE_MEASURE = 1,
            STATE_LED_ON,
            STATE_LED_OFF,
            STATE_SERVO_MOVEMENT,
            STATE_WAIT_NEXT
        };
    };
}

#endif