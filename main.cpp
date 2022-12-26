#include "mbed.h"
#include "ICM_20948.h"
#include <cstdio>
#include <cstring>

using namespace ECE4180;

ICM_20948 icm(p28, p27);
// main() runs in its own thread in the OS
int main()
{    
    char* connection_confirmation = "Connected to mbed\r\n";
    

    
    DPRINT("WHO_AM_I: %x\r\n", icm . whoami());

    if (!icm . isConnected()) {
        DPRINT("Cannot detect ICM 20948\r\n");
        return 1;
    }

    icm . write(PWR_MGMT_1, READ_FLAGS);
    icm . write(PWR_MGMT_1, 0x01);
  
    // ICM_20948_selfTest(icm, &pc);

    ICM_20948_BANK_DATA data;
    icm . read (FIFO_EN_2, data);

    DPRINT("ICM command returned: %d\r\n", data . RAW);

    icm . setBank(BANK_2);

    icm . read (REG_BANK_SEL, data);

    DPRINT("ICM at bank: %d\r\n", data . REG_BANK_SEL . USER_BANK);

    icm . setBank(BANK_0);

    ICM_20948_selfTest(icm);

    DPRINT("WHO_AM_I: %x\r\n", icm . whoami());

    return 0;
}

