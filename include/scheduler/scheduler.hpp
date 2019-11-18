#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "scheduler/task.hpp"

#define TICK_INTV 50

class Scheduler
{
public:
    Scheduler();
    void add(Task *task, unsigned int interval);
    void remove(Task *task);
    void clear();
    void schedule();
};

#endif