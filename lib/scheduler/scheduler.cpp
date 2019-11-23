#include "scheduler.h"

using namespace smartradar;

Scheduler::Scheduler() {
    clear();
}

void Scheduler::add(Task *task, unsigned int interval) {
    TaskInfo *iter = tasks;
    TaskInfo *endptr = tasks + MAX_TASKS;

    for ( ; iter < endptr; iter++) {
        if (iter->task == nullptr) {
            iter->task = task;
            iter->interval = interval;
            iter->elapsed = 0;
            taskCount += 1;
            return;
        }
    }
}

void Scheduler::remove(Task *task) {
    TaskInfo *iter = tasks;
    TaskInfo *endptr = tasks + MAX_TASKS;

    for ( ; iter < endptr; iter++) {
        if (iter->task == task) {
            iter->task = nullptr;
            taskCount -= 1;
            return;
        }
    }
}

void Scheduler::has(Task *task) {
    
}

void Scheduler::clear() {
    TaskInfo *iter = tasks;
    TaskInfo *endptr = tasks + MAX_TASKS;

    for ( ; iter < endptr; iter++) {
        iter->task = nullptr;
    }

    taskCount = 0;
}

void Scheduler::schedule() {
    TaskInfo *iter = tasks;
    TaskInfo *endptr = tasks + MAX_TASKS;

    for ( ; iter < endptr; iter++) {
        if (iter->task == nullptr) {
            continue;
        }
        
        if (iter->task->isComplete()) {
            remove(iter->task);
            continue;
        }

        if (iter->elapsed < iter->interval) {
            iter->elapsed++;
            continue;
        }

        iter->task->step();
        iter->elapsed = 0;
    }
}

unsigned int Scheduler::getTaskCount() {
    return taskCount;
}