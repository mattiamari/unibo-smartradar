#ifndef SMARTRADAR_PIRIMPL_H
#define SMARTRADAR_PIRIMPL_H

#include "pir.h"

#include <Arduino.h>
#include "eventemitter.h"

namespace smartradar
{
    class PirImpl : public EventEmitter, public Pir {
    public:
        PirImpl() {};
        void onDetect();
        unsigned int getHandlersCount();
        EventHandler** getHandlers();
    };
}

#endif
