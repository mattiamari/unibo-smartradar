#include <unity.h>

#include "test_scheduler.h"
#include "test_scanstatus.h"

int main(int argc, char **argv) {
    execute_scheduler();
    execute_scanstatus();
    
    return 0;
}