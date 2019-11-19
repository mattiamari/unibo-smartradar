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
    };
}

#endif