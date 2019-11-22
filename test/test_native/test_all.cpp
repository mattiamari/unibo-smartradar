#include <unity.h>

#include "test_scheduler.h"
#include "test_scanstatus.h"
#include "test_scanner.h"
#include "test_loopscanner.h"

int main(int argc, char **argv) {
    execute_scheduler();
    execute_scanstatus();
    execute_scanner();
    execute_loopscanner();
    
    return 0;
}