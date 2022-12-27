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
    // icm . disableInterrupts();
    // icm . disableFIFO();

    printf("Connected to mbed\r\n");    

    if (!icm . isConnected()) {
        printf("Cannot detect ICM 20948\r\n");
        return 1;
    }
    
    printf("Connected to ICM 20948\r\n");

    // ICM_20948_selfTest(icm);

    // icm . enableTemp();
    // icm . sleep();

    // int counter = 0;
    // while (1) {
    //     printf("[%4d] Current temperature: %7.3f degrees C\n", counter, icm . getTemp());
    //     thread_sleep_for(30);

    //     if (counter == 30) {
    //         icm . wakeup();
    //     }
    //     counter++;
    // }

    icm . enableAccel();
    // icm . sleep();

    ECE4180::ICM_20948::BANK_DATA data;
    icm . setBank(ECE4180::ICM_20948::BANK_2);
    data . RAW = 0;
    data . ACCEL_CONFIG . ACCEL_FCHOICE = 1;
    data . ACCEL_CONFIG . ACCEL_FS_SEL = 0x0;
    data . ACCEL_CONFIG . ACCEL_DLPFCFG = 0x1;
    icm  . write(ECE4180::ICM_20948::ACCEL_CONFIG, data);

    data . RAW = 0;
    
    icm . setBank(ECE4180::ICM_20948::BANK_0);
    icm . read (ECE4180::ICM_20948::PWR_MGMT_2, data);

    printf("%x <- accel enabled\r\n", data . PWR_MGMT_2 . DISABLE_ACCEL);

    int counter = 0;
    ECE4180::vec3 accelReadings;
    while (1) {
        icm . getAcc(accelReadings);
        printf("[%4d] Current Accel X: %7.3f Y: %7.3f Z%7.3f\r\n", counter, accelReadings . x, accelReadings . y, accelReadings . z);
        thread_sleep_for(30);

        // if (counter == 30) {
            // icm . wakeup();
        // }
        counter++;
    }
    return 0;
}

