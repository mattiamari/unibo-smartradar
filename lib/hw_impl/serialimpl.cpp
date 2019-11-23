#include "serialimpl.h"

using namespace smartradar;

void SerialImpl::print(char *msg) {
    ::Serial.print(msg);  
}

void SerialImpl::println(char *msg) {
    ::Serial.println(msg);  
}
