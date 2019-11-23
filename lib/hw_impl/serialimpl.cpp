#include "serialimpl.h"

using namespace smartradar;

void SerialImpl::print(const char *msg) {
    ::Serial.print(msg);
}

void SerialImpl::println(const char *msg) {
    ::Serial.println(msg);
}
