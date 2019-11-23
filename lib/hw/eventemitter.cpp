#include "eventemitter.h"

using namespace smartradar;

EventEmitter::EventEmitter() {
    handlersCount = 0;
}

void EventEmitter::addEventHandler(EventHandler *handler) {
    if(handlersCount >= MAX_HANDLERS){
        return;
    }
    handlers[handlersCount] = handler;
    handlersCount++;
}
