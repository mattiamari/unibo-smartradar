#include "test_serialupdater.h"

#include <unity.h>
#include <serialupdater.h>
#include <serial.h>
#include <scanstatus.h>

#include <string.h>

#include <stdio.h>

using namespace smartradar;

class DummySerial : public Serial
{
public:
    char buf[1024];

    void print(const char *text) {
        strncat(buf, text, 1024);
    }

    void println(const char *text) {
        print(text);
        print("\n");
    }
};

void test_should_write_json() {
    DummySerial serial = DummySerial();
    ScanStatus status = ScanStatus();
    SerialUpdater updater = SerialUpdater(&serial, &status);

    status.setCurrentMode(MODE_AUTO);
    status.setScanDuration(2000);
    status.setCurrentSlice(0);

    updater.step();

    // only compare the first 70 chars
    int res = strncmp(serial.buf, "{\"m\":\"a\",\"a\":0,\"s\":16,\"sd\":2000,\"cs\":0,\"me\":[", 45);

    TEST_ASSERT_EQUAL(0, res);
}

void execute_serialupdater() {
    UNITY_BEGIN();

    RUN_TEST(test_should_write_json);

    UNITY_END();
}
