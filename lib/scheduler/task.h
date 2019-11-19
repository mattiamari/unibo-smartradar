#ifndef SMARTRADAR_TASK_H
#define SMARTRADAR_TASK_H

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