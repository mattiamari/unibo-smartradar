#include <unity.h>

#include <scanstatus.h>

using namespace smartradar;

void test_can_create(void) {
    ScanStatus ss = ScanStatus();

    
}

void execute_scanstatus() {
    UNITY_BEGIN();

    RUN_TEST(test_can_create);

    UNITY_END();
}