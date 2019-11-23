#ifndef SMARTRADAR_BUTTONIMPL_H
#define SMARTRADAR_BUTTONIMPL_H

#include <Arduino.h>
#include "button.h"
#include "eventemitter.h"

namespace smartradar
{
    class ButtonImpl : public EventEmitter, public Button {
    private:
        byte pin_;

    public:
        ButtonImpl();
        void onPress();
    };
}

#endif
