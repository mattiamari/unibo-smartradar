#ifndef SMARTRADAR_EVENTHANDLER_H
#define SMARTRADAR_EVENTHANDLER_H

namespace smartradar
{
    class EventHandler {
    public:
        EventHandler() {};
        ~EventHandler() {};
        virtual void handle() = 0;
    };
}

#endif
