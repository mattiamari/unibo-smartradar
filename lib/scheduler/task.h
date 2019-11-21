#ifndef SMARTRADAR_TASK_H
#define SMARTRADAR_TASK_H

#define TASK_WAIT(COUNTER, DELAY) \
{ \
    if ((COUNTER) < (DELAY)) { \
        (COUNTER) += 1; \
        return; \
    } \
    (COUNTER) = 0; \
}

namespace smartradar
{
    class Task
    {
    public:
        Task() {}
        ~Task() {}
        virtual void step() = 0;
        virtual bool isComplete() = 0;
    };
}

#endif