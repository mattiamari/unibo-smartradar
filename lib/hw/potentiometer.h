#ifndef SMARTRADAR_POTENTIOMETER_H
#define SMARTRADAR_POTENTIOMETER_H

namespace smartradar
{
    class Potentiometer
    {
    public:
        Potentiometer() {};
        ~Potentiometer() {};
        virtual int getReading() = 0;
    };
}

#endif
