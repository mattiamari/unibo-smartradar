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
    LoopScanner sc = LoopScanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);

    servo.setAngle(0);
    sonar.reading = 1.0;

    TEST_ASSERT_FALSE(status.isAlarmActive());

    // States are
    // ServoMovement -> Measure -> LedOn -> LedOff -> WaitNext
    for (int i = 0; i < SCAN_SLICES * 5; i++) {

    }
}

void execute_loopscanner() {
    UNITY_BEGIN();

    RUN_TEST(test_should_create_loopscanner);

    UNITY_END();
}