#ifndef SMARTRADAR_SONARIMPL_H
#define SMARTRADAR_SONARIMPL_H

#include "sonar.h"
#include "Arduino.h"

namespace smartradar
{
    class SonarImpl : public Sonar {
    private:
        short trigPin_;
        short echoPin_;
        const float vs = 331.45 + 0.62*20;
    
    public:
        SonarImpl(short trigPin, short echoPin);
        float getReading();
        float getDistanceMin();
        float getDistanceMax();
    };
}

#endif
