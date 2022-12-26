#include "mbed.h"
#include "ICM_20948.h"
#include <cstdio>
#include <cstring>

ECE4180::ICM_20948::ICM_20948 icm(p28, p27);
// main() runs in its own thread in the OS
int main()
{    
    icm . reset();
    icm . setClockDefault();

    printf("Connected to mbed\r\n");    
    printf("WHO_AM_I: %x\r\n", icm . whoami());

    if (!icm . isConnected()) {
        printf("Cannot detect ICM 20948\r\n");
        return 1;
    }
    
    ICM_20948_selfTest(icm);

    // icm . enableTemp();
    // icm . sleep();

    // int counter = 0;
    // while (1) {
    //     printf("[%4d] Current temperature: %7.3f degrees C\n", counter, icm . getTemp());
    //     thread_sleep_for(30);

    //     if (counter == 90) {
    //         icm . wakeup();
    //     }
    //     counter++;
    // }
    return 0;
}

