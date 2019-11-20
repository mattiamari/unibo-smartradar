#include <unity.h>

#include <scheduler.h>
#include <task.h>


using namespace smartradar;

class DummyTask : public Task
{
public:
    unsigned int steps = 0;
    bool complete;

    DummyTask() {
        complete = false;
    }

    void step() {
        steps++;
    }

    bool isComplete() {
        return complete;
    }
};

void test_dummy(void) {
    DummyTask task = DummyTask();

    TEST_ASSERT_EQUAL(0, task.steps);
    task.step();
    TEST_ASSERT_EQUAL(1, task.steps);
}

void test_can_create_scheduler(void) {
    Scheduler sched = Scheduler();

    TEST_ASSERT_EQUAL(0, sched.getTaskCount());
}

void test_can_add_task(void) {
    Scheduler sched = Scheduler();
    DummyTask task = DummyTask();

    sched.add((Task*)&task, 100);
    TEST_ASSERT_EQUAL(1, sched.getTaskCount());
}

void test_can_remove_task(void) {
    Scheduler sched = Scheduler();
    DummyTask task = DummyTask();

    sched.add((Task*)&task, 100);
    TEST_ASSERT_EQUAL(1, sched.getTaskCount());

    sched.remove((Task*)&task);
    TEST_ASSERT_EQUAL(0, sched.getTaskCount());
}

void test_can_clear_all_tasks(void) {
    Scheduler sched = Scheduler();
    DummyTask task1 = DummyTask();
    DummyTask task2 = DummyTask();

    sched.add((Task*)&task1, 10);
    sched.add((Task*)&task2, 50);

    TEST_ASSERT_EQUAL(2, sched.getTaskCount());

    sched.clear();
    TEST_ASSERT_EQUAL(0, sched.getTaskCount());
}

void test_can_schedule_one_task(void) {
    Scheduler sched = Scheduler();
    DummyTask task = DummyTask();

    sched.add((Task*)&task, 2);

    TEST_ASSERT_EQUAL(0, task.steps);

    sched.schedule();
    TEST_ASSERT_EQUAL(0, task.steps);

    sched.schedule();
    TEST_ASSERT_EQUAL(0, task.steps);

    sched.schedule();
    TEST_ASSERT_EQUAL(1, task.steps);

    for (int i = 0; i < 16; i++) {
        sched.schedule();
    }

    TEST_ASSERT_EQUAL(6, task.steps);
}

void test_can_schedule_multiple_tasks(void) {
    Scheduler sched = Scheduler();
    DummyTask task1 = DummyTask();
    DummyTask task2 = DummyTask();
    DummyTask task3 = DummyTask();
    DummyTask task4 = DummyTask();

    sched.add((Task*)&task1, 4);
    sched.add((Task*)&task2, 1);
    sched.add((Task*)&task3, 11);
    sched.add((Task*)&task4, 0);

    for (int i = 0; i < 64; i++) {
        sched.schedule();
    }

    TEST_ASSERT_EQUAL(12, task1.steps);
    TEST_ASSERT_EQUAL(32, task2.steps);
    TEST_ASSERT_EQUAL(5, task3.steps);
    TEST_ASSERT_EQUAL(64, task4.steps);
}

void test_completed_tasks_are_removed(void) {
    Scheduler sched = Scheduler();
    DummyTask task1 = DummyTask();
    
    sched.add((Task*)&task1, 1);

    TEST_ASSERT_EQUAL(1, sched.getTaskCount());
    
    for (int i = 0; i < 2; i++) {
        sched.schedule();
    }

    TEST_ASSERT_EQUAL(1, task1.steps);

    task1.complete = true;

    for (int i = 0; i < 2; i++) {
        sched.schedule();
    }

    TEST_ASSERT_EQUAL(1, task1.steps);
    TEST_ASSERT_EQUAL(0, sched.getTaskCount());
}

void execute_scheduler() {
    UNITY_BEGIN();

    RUN_TEST(test_dummy);
    RUN_TEST(test_can_create_scheduler);
    RUN_TEST(test_can_add_task);
    RUN_TEST(test_can_remove_task);
    RUN_TEST(test_can_clear_all_tasks);
    RUN_TEST(test_can_schedule_one_task);
    RUN_TEST(test_can_schedule_multiple_tasks);
    RUN_TEST(test_completed_tasks_are_removed);

    UNITY_END();
}