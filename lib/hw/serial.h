#ifndef SMARTRADAR_SERIAL_H
#define SMARTRADAR_SERIAL_H

#include <stdio.h>

namespace smartradar
{
    class Serial{
    public:
        Serial() {};
        ~Serial() {};
        virtual void print(char *text) = 0;
        virtual void println(char *text) = 0;
    };
}

#endif