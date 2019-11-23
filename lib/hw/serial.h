#ifndef SMARTRADAR_SERIAL_H
#define SMARTRADAR_SERIAL_H

#include <stdio.h>

namespace smartradar
{
    class Serial{
    public:
        Serial() {};
        ~Serial() {};
        virtual void print(const char *text) = 0;
        virtual void println(const char *text) = 0;
    };
}

#endif
