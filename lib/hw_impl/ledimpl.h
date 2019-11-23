#ifndef SMARTRADAR_LEDIMPL_H
#define SMARTRADAR_LEDIMPL_H

#include "led.h"
#include <Arduino.h>

namespace smartradar
{
    class LedImpl : public Led {
    private:
        byte pin_;
        bool ledState;

    public:
        LedImpl(byte pin);
        bool isOn();
        void turnOn();
        void turnOff();
        void toggle();
    };
}

#endif
