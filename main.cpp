#include "mbed.h"
#include "ICM_20948.h"
#include <cstdio>
#include <cstring>

using namespace ECE4180::ICM_20948;

ICM_20948 icm(p28, p27);
// main() runs in its own thread in the OS
int main()
{    
    DPRINT("Connected to mbed\r\n");    
    DPRINT("WHO_AM_I: %x\r\n", icm . whoami());

    if (!icm . isConnected()) {
        DPRINT("Cannot detect ICM 20948\r\n");
        return 1;
    }
    
    ICM_20948_selfTest(icm);
    return 0;
}

