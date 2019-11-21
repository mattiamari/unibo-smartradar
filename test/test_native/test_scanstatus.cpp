#include <unity.h>

#include <scanstatus.h>

using namespace smartradar;

void test_can_create_scanstatus(void) {
    ScanStatus ss = ScanStatus();

    Measure *measures = ss.getMeasures();

    TEST_ASSERT_EQUAL(false, ss.isAlarmActive());

    for (int i = 0; i < SCAN_SLICES; i++) {
        TEST_ASSERT_EQUAL(0.0, measures[i].distance);
        TEST_ASSERT_EQUAL(i, measures[i].sliceIdx);
    }
}

void test_can_update_measure(void) {
    ScanStatus ss = ScanStatus();
    Measure *measures = ss.getMeasures();
    Measure newMeasure = {0, 0, 10.0};

    TEST_ASSERT_EQUAL(0.0, measures[0].distance);

    ss.updateMeasure(&newMeasure);

    TEST_ASSERT_EQUAL(10.0, measures[0].distance);
}

void test_clear_measures_sets_all_zero_distances(void) {
    ScanStatus ss = ScanStatus();
    Measure *measures = ss.getMeasures();

    Measure m0 = {0, 0, 10.0};
    Measure m1 = {1, 70, 20.0};
    Measure m2 = {2, 140, 5.0};

    ss.updateMeasure(&m0);
    ss.updateMeasure(&m1);
    ss.updateMeasure(&m2);

    TEST_ASSERT_EQUAL(10.0, measures[0].distance);
    TEST_ASSERT_EQUAL(20.0, measures[1].distance);
    TEST_ASSERT_EQUAL(5.0, measures[2].distance);
    
    ss.clearMeasures();

    TEST_ASSERT_EQUAL(0.0, measures[0].distance);
    TEST_ASSERT_EQUAL(0.0, measures[1].distance);
    TEST_ASSERT_EQUAL(0.0, measures[2].distance);
}

void test_set_alarm_state(void) {
    ScanStatus ss = ScanStatus();

    TEST_ASSERT_FALSE_MESSAGE(ss.isAlarmActive(), "Initial condition");

    ss.setAlarm(true);
    TEST_ASSERT_TRUE_MESSAGE(ss.isAlarmActive(), "Set true");

    ss.setAlarm(false);
    TEST_ASSERT_FALSE_MESSAGE(ss.isAlarmActive(), "Set false");
}

void execute_scanstatus() {
    UNITY_BEGIN();

    RUN_TEST(test_can_create_scanstatus);
    RUN_TEST(test_can_update_measure);
    RUN_TEST(test_clear_measures_sets_all_zero_distances);
    RUN_TEST(test_set_alarm_state);

    UNITY_END();
}