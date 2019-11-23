#include "test_loopscanner.h"

#include <unity.h>
#include <loopscanner.h>
#include <scanstatus.h>
#include <mock_hw.h>

using namespace smartradar;

static DummyServo servo = DummyServo();
static DummySonar sonar = DummySonar();
static DummyLed led = DummyLed();
static ScanStatus status = ScanStatus();

void test_should_create_loopscanner() {
    LoopScanner sc = LoopScanner(&servo, &sonar, &led);
}

void test_should_reset_alarm_when_no_detect() {
    servo.setAngle(0);
    status.setAlarm(false);

    LoopScanner sc = LoopScanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);
    sc.setScanTime(0);

    sonar.reading = 1.0;

    TEST_ASSERT_FALSE_MESSAGE(status.isAlarmActive(), "Alarm false before test");

    // ServoMovement -> Measure -> LedOn -> LedOff -> WaitNext
    int requiredTicks = 
        /* 4 ticks per slice */ (5 * SCAN_SLICES)
        /* led blink */ + (BLINK_DELAY_TICKS * SCAN_SLICES);

    for (int i = 0; i < requiredTicks; i++) {
        sc.step();
    }

    TEST_ASSERT_TRUE(status.isAlarmActive());

    sonar.reading = 0.0;

    // ServoMovement -> Measure -> WaitNext
    for (int i = 0; i < 3 * SCAN_SLICES + 3; i++) {
        sc.step();
    }

    TEST_ASSERT_FALSE(status.isAlarmActive());
}

void execute_loopscanner() {
    UNITY_BEGIN();

    RUN_TEST(test_should_create_loopscanner);
    RUN_TEST(test_should_reset_alarm_when_no_detect);

    UNITY_END();
}