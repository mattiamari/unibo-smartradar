#include "pirimpl.h"

using namespace smartradar;

void PirImpl::onDetect() {
    for(unsigned int i = 0; i < handlersCount; i++){
        handlers[i]->handle();
    }
}
