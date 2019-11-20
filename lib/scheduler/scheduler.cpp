#include "scheduler.h"

using namespace smartradar;

Scheduler::Scheduler() {
    clear();
}

void Scheduler::add(Task *task, unsigned int interval) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].task == nullptr) {
            tasks[i].task = task;
            tasks[i].interval = interval;
            tasks[i].elapsed = 0;
            taskCount += 1;
            return;
        }
    }
}

void Scheduler::remove(Task *task) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].task == task) {
            tasks[i].task = nullptr;
            taskCount -= 1;
            return;
        }
    }
}

void Scheduler::clear() {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].task = nullptr;
    }
    taskCount = 0;
}

void Scheduler::schedule() {
    TaskInfo *iter = tasks;
    TaskInfo *endptr = tasks + MAX_TASKS;

    while (iter < endptr) {
        if (iter->task == nullptr) {
            iter++;
            continue;
        }
        
        if (iter->task->isComplete()) {
            remove(iter->task);
            iter++;
            continue;
        }

        if (iter->elapsed < iter->interval) {
            iter->elapsed++;
            iter++;
            continue;
        }

        iter->task->step();
        iter->elapsed = 0;

        iter++;
    }
}

unsigned int Scheduler::getTaskCount() {
    return taskCount;
}