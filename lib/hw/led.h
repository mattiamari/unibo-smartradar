#ifndef SMARTRADAR_LED_H
#define SMARTRADAR_LED_H

namespace smartradar
{
    class Led
    {
    public:
        Led() {};
        ~Led() {};
        virtual bool isOn() = 0;
        virtual void turnOn() = 0;
        virtual void turnOff() = 0;
        virtual void toggle() = 0;
    };
}

#endif