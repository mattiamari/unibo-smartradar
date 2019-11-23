#ifndef SMARTRADAR_SERIALIMPL_H
#define SMARTRADAR_SERIALIMPL_H

#include "serial.h"

#include <Arduino.h>

namespace smartradar
{
    class SerialImpl : public Serial {
    public:
        SerialImpl() {};
        void println(const char *msg);
        void print(const char *msg);
    };
}

#endif
