#ifndef SMARTRADAR_SCHEDULER_H
#define SMARTRADAR_SCHEDULER_H

#include "task.h"

#define TICK_INTERVAL_MS 60
#define MAX_TASKS 16

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
        void add(Task *task);
        void remove(Task *task);
        bool has(Task *task);
        bool hasOfType(TaskType type);
        void clear();
        void schedule();
        unsigned int getTaskCount();

    private:
        TaskInfo tasks[MAX_TASKS];
        unsigned int taskCount;
    };
}

#endif
