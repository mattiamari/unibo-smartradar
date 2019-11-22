#include "test_scanner.h"

#include <unity.h>

#include <scanner.h>
#include <scanstatus.h>
#include <mock_hw.h>
#include <scheduler.h>

using namespace smartradar;

static DummyServo servo = DummyServo();
static DummySonar sonar = DummySonar();
static DummyLed led = DummyLed();
static ScanStatus status = ScanStatus();


void test_slice_to_angle() {
    TEST_ASSERT_EQUAL(15, sliceToAngle(0, 16, 10, 170));
    TEST_ASSERT_EQUAL(165, sliceToAngle(15, 16, 10, 170));
}

void test_can_create_scanner() {
    Scanner sc = Scanner(&servo, &sonar, &led);
}

void test_should_move_servo() {
    Scanner sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);

    servo.setAngle(0);
    sonar.reading = 0.0;

    // ServoMovement -> Measure -> WaitNext
    // 2 times should move to slice with index 1
    for (int i = 0; i < 6; i++) {
        sc.step();
    }

    TEST_ASSERT_EQUAL(sliceToAngle(1, SCAN_SLICES, servo.getAngleMin(), servo.getAngleMax()), servo.getAngle());
}

void test_should_complete_when_end_reached() {
    Scanner sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);

    servo.setAngle(0);
    sonar.reading = 0.0;

    TEST_ASSERT_FALSE(sc.isComplete());

    // it takes 3 ticks for each slice because we have 3 states to cycle on
    // ServoMovement -> Measure -> WaitNext
    for (int i = 0; i < SCAN_SLICES * 3 + 1; i++) {
        sc.step();
    }

    TEST_ASSERT_EQUAL(SCAN_SLICES - 1, status.getCurrentSlice());
    TEST_ASSERT_TRUE(sc.isComplete());
}

void test_should_complete_when_end_reached_backwards() {
    Scanner sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);

    servo.setAngle(servo.getAngleMax());
    sonar.reading = 0.0;

    TEST_ASSERT_FALSE(sc.isComplete());

    // it takes 3 ticks for each slice because we have 3 states to cycle on
    // ServoMovement -> Measure -> WaitNext
    for (int i = 0; i < SCAN_SLICES * 3 + 1; i++) {
        sc.step();
    }

    TEST_ASSERT_EQUAL(0, status.getCurrentSlice());
    TEST_ASSERT_TRUE(sc.isComplete());
}

void test_should_update_measures_when_in_range() {
    Scanner sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);
    servo.setAngle(0);
    sonar.reading = 1.0;

    // it could take SCAN_SLICES * 4 steps to complete the scan
    // because we cycle through
    // ServoMovement -> Measure -> LedOn -> LedOff -> WaitNext
    for (int i = 0; i < SCAN_SLICES * 5; i++) {
        sc.step();
    }

    TEST_ASSERT_EQUAL_FLOAT(1.0, status.getMeasures()[0].distance);
    TEST_ASSERT_EQUAL_FLOAT(1.0, status.getMeasures()[SCAN_SLICES - 1].distance);
}

void test_should_blink_led_on_detect() {
    Scanner sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);
    servo.setAngle(0);
    sonar.reading = 1.0;

    // it takes 3 ticks for changing states like
    // ServoMovement -> Measure -> LedOn
    for (int i = 0; i < 3; i++) {
        sc.step();
    }

    TEST_ASSERT_TRUE(led.state);

    sc.step();
    // State should now be LedOff

    // led should stay on for 40ms so it takes (40 / TICK_INTERVAL_MS) ticks
    for (int i = 0; i < 40 / TICK_INTERVAL_MS; i++) {
        sc.step();
    }

    TEST_ASSERT_FALSE(led.state);
}

void test_should_not_blink_led_when_not_detecting() {
    servo.setAngle(0);

    Scanner sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);

    // test with too near value
    sonar.reading = 0.3;

    // it takes 3 ticks to change states like
    // ServoMovement -> Measure -> LedOn -> LedOff
    // and BLINK_DELAY_TICKS to change LedOff -> WaitNext
    //
    // We stop before going to WaitNext so currentSlice does not get updated
    for (int i = 0; i < 3 + BLINK_DELAY_TICKS; i++) {
        sc.step();
    }

    TEST_ASSERT_EQUAL(0, status.getCurrentSlice());
    TEST_ASSERT_EQUAL_FLOAT(0.3, status.getMeasures()[0].distance);
    TEST_ASSERT_FALSE_MESSAGE(led.state, "Too near value");

    // now go to WaitNext
    sc.step();

    // test with too far value
    sonar.reading = 4.0;

    // it takes 3 ticks to change states like
    // ServoMovement -> Measure -> WaitNext
    //
    // We stop at 2 so currentSlice does not get updated
    for (int i = 0; i < 2; i++) {
        sc.step();
    }

    TEST_ASSERT_EQUAL(1, status.getCurrentSlice());
    TEST_ASSERT_EQUAL_FLOAT(4.0, status.getMeasures()[1].distance);
    TEST_ASSERT_FALSE_MESSAGE(led.state, "Too far value");
}

void test_scan_should_take_specified_scantime() {
    Scanner sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);
    servo.setAngle(0);
    sonar.reading = 0.0;

    unsigned int scanTime = 2000;
    sc.setScanTime(scanTime);

    // When sonar is not detecting, Scanner end up being
    // ServoMovement -> Measure -> WaitNext
    // so it should take SCAN_SLICES * 3
    // plus some wait time after each measure amounting to scanTime / TICK_INTERVAL_MS
    //
    // This "(scanTime / TICK_INTERVAL_MS / SCAN_SLICES) * SCAN_SLICES" is needed in order
    // to account for lost precision when doing "scanTime / TICK_INTERVAL_MS / SCAN_SLICES"
    // in the Scanner's WaitNext state
    unsigned int expectedTicks = (SCAN_SLICES * 3) + (scanTime / TICK_INTERVAL_MS / SCAN_SLICES) * SCAN_SLICES;

    for (int i = 0; i < expectedTicks; i++) {
        sc.step();
    }

    TEST_ASSERT_FALSE(sc.isComplete());

    sc.step();

    TEST_ASSERT_TRUE(sc.isComplete());
}

void test_detected_should_be_true_on_detect() {
    Scanner sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);
    servo.setAngle(0);
    sonar.reading = 1.0;

    // Should run through
    // ServoMovement -> Measure -> LedOn -> LedOff -> WaitNext
    unsigned int ticks = 5;

    TEST_ASSERT_FALSE(sc.hasDetected());

    for (int i = 0; i < ticks; i++) {
        sc.step();
    }

    TEST_ASSERT_TRUE(sc.hasDetected());
}

void test_should_move_servo_to_nearest_end() {
    sonar.reading = 0.0;

    // right bound
    servo.setAngle(150);
    Scanner sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);

    sc.step();

    TEST_ASSERT_EQUAL_MESSAGE(sliceToAngle(15, SCAN_SLICES, servo.getAngleMin(), servo.getAngleMax()), servo.getAngle(), "Right bound");

    // left bound
    servo.setAngle(50);
    sc = Scanner(&servo, &sonar, &led);
    sc.setScanStatus(&status);

    sc.step();

    TEST_ASSERT_EQUAL_MESSAGE(sliceToAngle(0, SCAN_SLICES, servo.getAngleMin(), servo.getAngleMax()), servo.getAngle(), "Left bound");
}

void execute_scanner() {
    UNITY_BEGIN();

    RUN_TEST(test_slice_to_angle);
    RUN_TEST(test_can_create_scanner);
    RUN_TEST(test_should_move_servo);
    RUN_TEST(test_should_complete_when_end_reached);
    RUN_TEST(test_should_complete_when_end_reached_backwards);
    RUN_TEST(test_should_update_measures_when_in_range);
    RUN_TEST(test_should_blink_led_on_detect);
    RUN_TEST(test_should_not_blink_led_when_not_detecting);
    RUN_TEST(test_scan_should_take_specified_scantime);
    RUN_TEST(test_detected_should_be_true_on_detect);
    RUN_TEST(test_should_move_servo_to_nearest_end);

    UNITY_END();
}