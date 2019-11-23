#include "buttonimpl.h"

using namespace smartradar;

void ButtonImpl::onPress() {
    for(unsigned int i = 0; i < handlersCount; i++){
        handlers[i]->handle();  
    }
}
