#ifndef SMARTRADAR_SCHEDULER_H
#define SMARTRADAR_SCHEDULER_H

#include "task.h"

#define TICK_INTERVAL_MS 50
#define MAX_TASKS 8

namespace smartradar
{
    typedef struct TaskInfo_s {
        Task *task;
        unsigned int interval;
        unsigned int elapsed;
    } TaskInfo;

    class Scheduler
    {
    public:
        Scheduler();
        ~Scheduler() {};
        void add(Task *task, unsigned int interval);
        void remove(Task *task);
        void clear();
        void schedule();
        unsigned int getTaskCount();

    private:
        TaskInfo tasks[MAX_TASKS];
        unsigned int taskCount;
    };
}

#endif