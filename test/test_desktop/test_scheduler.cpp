#include "scheduler/scheduler.hpp"
#include "scheduler/task.hpp"

#include <unity.h>
#include <stdio.h>

class DummyTask : public Task
{
private:
    unsigned int ticks = 0;

public:
    void step() {
        ticks++;
    }

    bool isComplete() {
        return false;
    }

    unsigned int getElapsedTicks() {
        return ticks;
    }
};

void test_dummy(void) {
    DummyTask *task = new DummyTask();
    task->step();
    TEST_ASSERT(task->getElapsedTicks() == 1);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_dummy);

    UNITY_END();
    return 0;
}