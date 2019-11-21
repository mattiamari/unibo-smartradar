#ifndef SMARTRADAR_SONAR_H
#define SMARTRADAR_SONAR_H

namespace smartradar
{
    class Sonar
    {
    public:
        Sonar() {};
        ~Sonar() {};
        virtual float getReading() = 0;
        virtual float getDistanceMin() = 0;
        virtual float getDistanceMax() = 0;
    };
}

#endif