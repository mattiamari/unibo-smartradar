#ifndef SMARTRADAR_SONARIMPL_H
#define SMARTRADAR_SONARIMPL_H

#include "sonar.h"
#include "Arduino.h"

namespace smartradar
{
    class SonarImpl : public Sonar {
    private:
        byte trigPin_;
        byte echoPin_;
        const double vs = 331.45 + 0.62*20;
    
    public:
        SonarImpl(byte trigPin, byte echoPin);
        float getReading();
        float getDistanceMin();
        float getDistanceMax();
    };
}

#endif
