#ifndef SMARTRADAR_POTENTIOMETERIMPL_H
#define SMARTRADAR_POTENTIOMETERIMPL_H

#include "potentiometer.h"
#include <Arduino.h>

namespace smartradar {
    class PotentiometerImpl : public Potentiometer {

    private:
        short pin_;

    public:
        PotentiometerImpl(short pin);
        int getReading();
    };
}

#endif
