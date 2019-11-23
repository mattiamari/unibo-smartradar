#ifndef SMARTRADAR_EVENTEMITTER_H
#define SMARTRADAR_EVENTEMITTER_H

#include "eventhandler.h"

#define MAX_HANDLERS 1

namespace smartradar
{
    class EventEmitter {
    public:
        EventEmitter();
        void addEventHandler(EventHandler *handler);

    protected:
        EventHandler* handlers[MAX_HANDLERS];
        unsigned int handlersCount;
    };
}

#endif
