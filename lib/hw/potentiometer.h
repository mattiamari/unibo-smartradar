#ifndef SMARTRADAR_POTENTIOMETER_H
#define SMARTRADAR_POTENTIOMETER_H

namespace smartradar
{
    class Potentiometer
    {
    public:
        Potentiometer() {};
        ~Potentiometer() {};
        virtual unsigned int getReading() = 0;
    };
}

#endif