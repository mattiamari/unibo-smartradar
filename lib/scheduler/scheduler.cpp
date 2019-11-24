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
            iter->elapsed = interval;
            taskCount += 1;
            return;
        }
    }
}

void Scheduler::add(Task *task) {
    add(task, 0);
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

bool Scheduler::has(Task *task) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].task != nullptr && tasks[i].task == task) {
            return true;
        }
    }

    return false;
}

bool Scheduler::hasOfType(TaskType type) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (tasks[i].task != nullptr && tasks[i].task->getType() == type) {
            return true;
        }
    }

    return false;
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

    unsigned long before, diff;

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

        // before = millis();
        iter->task->step();
        iter->elapsed = 0;
        // diff = millis() - before;
        // ::Serial.print("task ");
        // ::Serial.print((int)iter->task);
        // ::Serial.print(": ");
        // ::Serial.println(diff);
    }
}

unsigned int Scheduler::getTaskCount() {
    return taskCount;
}
