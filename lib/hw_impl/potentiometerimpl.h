#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "Arduino.h"

namespace smartradar {
    class Potentiometer{

    private:
        byte pin_;
    
    public:
        Potentiometer(byte pin);
        int getReading(); 
    };
}

#endif
