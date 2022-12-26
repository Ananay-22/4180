#include "ICM_20948.h"
#include <cstdint>
#include <cstdio>

// TODO: make sure right bank is selected in command interface
// TODO: make sure that the commands before the temp/ sleep commit are all reading data, changing only bits to be updated, then writing the data.
namespace ECE4180 {
    namespace ICM_20948 {
        ICM_20948::ICM_20948(PinName sda, PinName scl) : I2C(sda, scl)
        {
            this -> frequency(400000);  // use fast (400 kHz) I2C
        }

        void ICM_20948::write(BANK_REGISTERS registerAddress, byte data)
        {
            BANK_DATA d;
            d . RAW = data;
            this -> write(registerAddress, d);
        }

        void ICM_20948::write(BANK_REGISTERS registerAddress, BANK_DATA data)
        {
            char tmp[2];
            tmp[0]=registerAddress;
            tmp[1]= data . RAW;
            ICM_20948_DPRINT("Writing Command: %2x %2x\r\n", tmp[0], tmp[1]);
            I2C :: write(ADDRESS,  tmp, 2, 0); // no stop
            thread_sleep_for(10);
            // TODO: check wait?
        }

        void ICM_20948::read(BANK_REGISTERS registerAddress, BANK_DATA& dest)
        {
            // D(
                // I AM SO DUMB
                // PUTTING THIS CHECK TO SEE IF THE ICM IS CONNECTED BEFORE A READ
                // EVEN FOR "DEBUGGING PURPOSES"
                // BREAKS THE CODE SINCE IT SWITCHES TO BANK_0
                // DUH DOY - Ananay Gupta
                // if (registerAddress != WHO_AM_I_ICM20948)  {
                //     if (!this -> isConnected()) {
                //         exit(1);
                //     }
                // }
            // );
            char tmp[1];
            tmp[0]=registerAddress;
            I2C ::  write(ADDRESS, tmp, 1, 1); // no stop
            I2C ::  read(ADDRESS, tmp, 1, 0); //stop
            thread_sleep_for(10);
            // Return data read from slave register
            dest . RAW = tmp[0];
            ICM_20948_DPRINT("Reading Command: %2x -> %2x\r\n", registerAddress, tmp[0]);
            // TODO: check wait?
        }

        byte ICM_20948::read(BANK_REGISTERS registerAddress)
        {
            BANK_DATA val;
            this -> read(registerAddress, val);
            return val . RAW;
        }

        byte ICM_20948::read(byte registerAddress) {
            return this -> read((BANK_REGISTERS) registerAddress);
        }


        void ICM_20948::setClockDefault()
        {
            BANK_DATA param;
            this -> setBank(BANK_0);
            // Get stable time source
            // Auto select clock source to be PLL gyroscope reference if ready else
            param . RAW = 0;
            param . PWR_MGMT_1 . CLKSEL = 0x1;
            this -> write(PWR_MGMT_1, param);
        }

        void ICM_20948::__init()
        {
            BANK_DATA param, value;

            this -> setClockDefault();
            // Switch to user bank 2
            this -> setBank(BANK_2);

            // todo -> change to class functions

            // Configure Gyro and Thermometer
            // Disable FSYNC and set gyro bandwidth to 51.2 Hz,
            // respectively;
            // minimum delay time for this setting is 5.9 ms, which means sensor fusion
            // update rates cannot be higher than 1 / 0.0059 = 170 Hz
            // DLPF_CFG = bits 2:0 = 011; this limits the sample rate to 1000 Hz for both
            // With the ICM20948, it is possible to get gyro sample rates of 32 kHz (!),
            // 8 kHz, or 1 kHz
            // Set gyroscope full scale range to 250 dps
            param . RAW = 0;
            param . GYRO_CONFIG_1 . GYRO_FCHOICE = 0x1;
            param . GYRO_CONFIG_1 . GYRO_DLPFCFG = 0x3;
            this -> write(GYRO_CONFIG_1, param);
            param . RAW = 0;
            param . TEMP_CONFIG . TEMP_DLPFCFG = 0x3;
            this -> write(TEMP_CONFIG, param);

            // Set sample rate = gyroscope output rate/(1 + GYRO_SMPLRT_DIV)
            // Use a 220 Hz rate; a rate consistent with the filter update rate
            // determined inset in CONFIG above.

            param . RAW = 0;
            param . GYRO_SMPLRT_DIV . GYRO_SMPLRT_DIV = 0x04;
            this -> write(GYRO_SMPLRT_DIV, param);

            param . RAW = 0;
            param . ACCEL_CONFIG . ACCEL_FS_SEL = 0x0; // Clear AFS bits [4:3]
            // TODO: check about setting the AScale -> is it being set to 0? how do we configure it here?
            param . ACCEL_CONFIG . ACCEL_FCHOICE = 0x1;
            param . ACCEL_CONFIG . ACCEL_DLPFCFG = 0x3;
            this -> write(ACCEL_CONFIG, param);

            // Set accelerometer sample rate configuration
            // It is possible to get a 4 kHz sample rate from the accelerometer by
            // choosing 1 for accel_fchoice_b bit [3]; in this case the bandwidth is
            // 1.13 kHz
            param . RAW = 0;
            param . ACCEL_SMPLRT_DIV_2 . ACCEL_SMPLRT_DIV = 0x04;
            this -> write(ACCEL_SMPLRT_DIV_2, param);

            // The accelerometer, gyro, and thermometer are set to 1 kHz sample rates,
            // but all these rates are further reduced by a factor of 5 to 200 Hz because
            // of the GYRO_SMPLRT_DIV setting

            // Switch to user bank 0
            this -> setBank(BANK_0);

            // Configure Interrupts and Bypass Enable
            // Set interrupt pin active high, push-pull, hold interrupt pin level HIGH
            // until interrupt cleared, clear on read of INT_STATUS, and enable
            // I2C_BYPASS_EN so additional chips can join the I2C bus and all can be
            // controlled by the Arduino as master.
            param . RAW = 0;
            param . INT_PIN_CFG . INT1_LATCH_INT_EN = 1;
            param . INT_PIN_CFG . BYPASS_EN = 1;
            this -> write(INT_PIN_CFG, param);
            // Enable data ready (bit 0) interrupt
            param . RAW = 0;
            param . INT_ENABLE_1 . RAW_DATA_0_RDY_EN = 1;
            this -> write(INT_ENABLE_1, param);
        }

        void ICM_20948::__calibrate()
        {
            this -> reset();
            this -> setClockDefault();

            // configure device for bias calculation
            this -> disableInterrupts();
            this -> disableFIFO();

            // turn on internal clock
            BANK_DATA param;
            param . RAW = 0;
            param . PWR_MGMT_1 . CLKSEL = 0x0;
            this -> write(PWR_MGMT_1, param);


            this -> disableUserControl();
            this -> resetFIFO();
            this -> resetDMP();

            this -> setFIFOSnapshot();

            this -> setBank(BANK_2);

            // todo -> finish. currently at bias calculation
        }


        void ICM_20948::setBank(Bank bank)
        {
            if (this -> currentBank == bank) return;
            this -> write(REG_BANK_SEL, bank);

            // OH NO I FORGOT THIS LINE BEFORE, IT REALLY MESSED THINGS UP
            this -> currentBank = bank;
        }

        void ICM_20948::reset()
        {
            this -> setBank(BANK_0);
            // reset device
            // Write a one to bit 7 reset bit; toggle reset device
            this -> write(PWR_MGMT_1, READ_FLAGS);

            // Reset FIFO and DMP
            this -> resetDMP();
            this -> resetFIFO();
        }

        void ICM_20948::disableFIFO()
        {
            this -> setBank(BANK_0);
            BANK_DATA param;

            param . RAW = 0;

            this -> write(FIFO_EN_1, param); // all flags in FIFO_EN_1 and FIFO_EN_2 should be 0
            this -> write(FIFO_EN_2, param);
        }

        void ICM_20948::disableInterrupts()
        {
            this -> setBank(BANK_0);
            BANK_DATA param;

            param . RAW = 0;
            this -> write(INT_ENABLE, param);
        }

        void ICM_20948::enableInterrupts()
        {
            this -> setBank(BANK_0);
            // TODO: be a bit smart about this, it should be able to handle all the different parameters datasheet: 7.1
            
            exit(1);
        }

        void ICM_20948::enableFIFO()
        {
            this -> setBank(BANK_0);
            // TODO: be a bit smart about this, it should be able to handle all the different parameters datasheet: 8.56/ 8.57
            
            exit(1);
        }

        void ICM_20948::resetDMP()
        {
            this -> setBank(BANK_0);
            BANK_DATA param;
            param . RAW = 0;
            param . USER_CTRL . DMP_RST = 1;

            this -> write(USER_CTRL, param);
        }

        void ICM_20948::resetFIFO()
        {
            this -> setBank(BANK_0);
            BANK_DATA param;
            param . RAW = 0;
            param . FIFO_RST . FIFO_RESET = 0x1F;
            this -> write(FIFO_RST, param);
            param . RAW = 0;
            this -> write(FIFO_RST, param);

        }

        void ICM_20948::resetFIFOSize()
        {
            this -> setBank(BANK_0);
            BANK_DATA param;
            param . RAW = 0;
            param . FIFO_RST . FIFO_RESET = 0x1F;
            this -> write(FIFO_RST, param);
            this -> write(FIFO_RST, param);

        }

        byte ICM_20948::whoami() {
            this -> setBank(BANK_0);
            return this -> read(WHO_AM_I);
        }

        bool ICM_20948::isICM_20948()
        {
            this -> setBank(BANK_0);
            return this -> whoami() == 0xEA;
        }

        bool ICM_20948::isConnected()
        {
            return this -> isICM_20948();
        }

        bool ICM_20948::isReady()
        {
            return this -> isConnected();
        }

        void ICM_20948::disableUserControl()
        {
            this -> setBank(BANK_0);
            BANK_DATA param;
            param . RAW = 0;
            this -> write(USER_CTRL, param);
        }

        void ICM_20948::setFIFOSnapshot()
        {
            this -> setBank(BANK_0);
            BANK_DATA param;
            param . RAW = 0x1F;
            this -> write(FIFO_MODE, param);
        }

        void ICM_20948::setFIFOStream()
        {
            this -> setBank(BANK_0);
            BANK_DATA param;
            param . RAW = 0x0;
            this -> write(FIFO_MODE, param);
        }

        void ICM_20948::enableTemp() {
            this -> setBank(BANK_0);
            BANK_DATA data;
            data . RAW = 0;
            this -> read  (PWR_MGMT_1, data);
            data . PWR_MGMT_1 . TEMP_DIS = 0;
            this -> write (PWR_MGMT_1, data);
        }

        void ICM_20948::disableTemp() {
            this -> setBank(BANK_0);
            BANK_DATA data;
            data . RAW = 0;
            this -> read  (PWR_MGMT_1, data);
            data . PWR_MGMT_1 . TEMP_DIS = 1;
            this -> write (PWR_MGMT_1, data);
        }

        void ICM_20948::sleep() {
            this -> setBank(BANK_0);
            BANK_DATA data;
            data . RAW = 0;
            this -> read (PWR_MGMT_1, data);
            data . PWR_MGMT_1 . SLEEP = 1;
            this -> write (PWR_MGMT_1, data);
        }

        void ICM_20948::wakeup() {
            this -> setBank(BANK_0);
            BANK_DATA data;
            data . RAW = 0;
            this -> read (PWR_MGMT_1, data);
            data . PWR_MGMT_1 . SLEEP = 0;
            this -> write (PWR_MGMT_1, data);
        }

        float ICM_20948::getTemp() {
            // todo: push/ pop bank
            BANK_DATA data;
            uint16_t temp_out;
            float retVal;

            const uint32_t RoomTempOffset  =      0; // deg C; datasheet pdf page 14
            const float    TempSensitivity = 333.87; // LSB/ deg C; datasheet pdf page 14
            
            this -> setBank(BANK_0);

            temp_out = 0;

            data . RAW = 0;
            this -> read(TEMP_OUT_H, data);
            temp_out = data . TEMP_OUT_H . TEMP_OUT_H << 8;

            data . RAW = 0;
            this -> read(TEMP_OUT_L, data);
            temp_out |= data . TEMP_OUT_L . TEMP_OUT_L;

            ICM_20948_DPRINT("Temperature measured: %d\n", temp_out);

            retVal = ((float) (temp_out - RoomTempOffset) / TempSensitivity) + 21; // datasheet 8.31
            return retVal;
        }


        // Accelerometer and gyroscope self test; check calibration wrt factory settings
        // Should return percent deviation from factory trim values, +/- 14 or less
        // deviation is a pass.
        void ICM_20948_selfTest(ICM_20948& icm)
        {
            uint8_t rawData[6] = {0, 0, 0, 0, 0, 0};
            uint8_t selfTest[6];
            int32_t gAvg[3] = {0}, aAvg[3] = {0}, aSTAvg[3] = {0}, gSTAvg[3] = {0};
            float factoryTrim[6];
            uint8_t FS = 0;
            int iters = 20;

            printf("Running ICM 20948 Self Test [%d iterations]\r\n", iters);


            BANK_DATA param, value;

            ICM_20948_DPRINT("1\n");

            icm . reset();
            icm . setClockDefault();


            ICM_20948_DPRINT("2\n");

            icm . setBank(BANK_2);
            ICM_20948_DPRINT("Current Bank: %x (should be 2)\n", icm . read(REG_BANK_SEL));


            param . RAW = 0;
            icm . write(GYRO_SMPLRT_DIV, param);

            param . GYRO_CONFIG_1 . GYRO_DLPFCFG = 0x2;
            param . GYRO_CONFIG_1 . GYRO_FS_SEL = 0x0;
            param . GYRO_CONFIG_1 . GYRO_FCHOICE = 0x1;

            icm . write(GYRO_CONFIG_1, 0x11);


            param . RAW = 0;
            param . ACCEL_CONFIG . ACCEL_DLPFCFG = 0x2;
            param . ACCEL_CONFIG . ACCEL_FS_SEL = 0x0;
            param . ACCEL_CONFIG . ACCEL_FCHOICE = 0x1;

            icm . write(ACCEL_CONFIG, 0x11);

            icm . setBank(BANK_0);         
            ICM_20948_DPRINT("Current Bank: %x (should be 0)\n", icm . read(REG_BANK_SEL));

            printf("Polling without test mode\r\n");
            for (int i = 0; i < iters; i++) {
                printf(".");
                fflush(stdout);
                for (int j = 0; j < 6; j++) {
                    rawData[j] = icm . read(ACCEL_XOUT_H + j);
                }

                aAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
                aAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
                aAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;

                for (int j = 0; j < 6; j++) {
                    rawData[j] = icm . read(GYRO_XOUT_H + j);
                }
                
                gAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
                gAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
                gAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
            }


            for (int i = 0; i < 3; i++) {
                aAvg[i] /= iters;
                gAvg[i] /= iters;
            }
            
            ICM_20948_DPRINT("3\n");
            icm . setBank(BANK_2);
            ICM_20948_DPRINT("Current Bank: %x (should be 2)\n", icm . read(REG_BANK_SEL));

            param . GYRO_CONFIG_1 . GYRO_DLPFCFG = 0x2;
            param . GYRO_CONFIG_1 . GYRO_FS_SEL = 0x0;
            param . GYRO_CONFIG_1 . GYRO_FCHOICE = 0x1;

            icm . write(GYRO_CONFIG_2, 0x38);


            param . RAW = 0;
            param . ACCEL_CONFIG . ACCEL_DLPFCFG = 0x2;
            param . ACCEL_CONFIG . ACCEL_FS_SEL = 0x0;
            param . ACCEL_CONFIG . ACCEL_FCHOICE = 0x1;

            icm . write(ACCEL_CONFIG_2, 0x1C);

            icm . setBank(BANK_0);         
            ICM_20948_DPRINT("Current Bank: %x (should be 0)\n", icm . read(REG_BANK_SEL));
            printf("\n\rPolling with test mode\r\n");
            for (int i = 0; i < iters; i++) {
                printf(".");
                fflush(stdout);
                for (int j = 0; j < 6; j++) {
                    rawData[j] = icm . read(ACCEL_XOUT_H + j);
                }

                aSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
                aSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
                aSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;

                for (int j = 0; j < 6; j++) {
                    rawData[j] = icm . read(GYRO_XOUT_H + j);
                }
                    
                gSTAvg[0] += (int16_t)(((int16_t)rawData[0] << 8) | rawData[1]) ;
                gSTAvg[1] += (int16_t)(((int16_t)rawData[2] << 8) | rawData[3]) ;
                gSTAvg[2] += (int16_t)(((int16_t)rawData[4] << 8) | rawData[5]) ;
            }


            for (int i = 0; i < 3; i++) {
                aSTAvg[i] /= iters;
                gSTAvg[i] /= iters;
            }



            ICM_20948_DPRINT("4\n");

            icm . setBank(BANK_2);

            icm . write(ACCEL_CONFIG_2, 0);
            icm . write(GYRO_CONFIG_2,  0);

        // todo: delay?

            icm . setBank(BANK_1);
            ICM_20948_DPRINT("Current Bank: %x (should be 1)\n", icm.read(REG_BANK_SEL));

            selfTest[0] = icm . read(SELF_TEST_X_ACCEL);
            selfTest[1] = icm . read(SELF_TEST_Y_ACCEL);
            selfTest[2] = icm . read(SELF_TEST_Z_ACCEL);
            selfTest[3] = icm . read(SELF_TEST_X_GYRO);
            selfTest[4] = icm . read(SELF_TEST_Y_GYRO);
            selfTest[5] = icm . read(SELF_TEST_Z_GYRO);
            
            ICM_20948_DPRINT("5\n");

            icm . setBank(BANK_0);


            // Retrieve factory self-test value from self-test code reads
            // FT[Xa] factory trim calculation
            factoryTrim[0] = (float)(2620/1<<FS)*(pow(1.01,((float)selfTest[0] - 1.0) ));
            // FT[Ya] factory trim calculation
            factoryTrim[1] = (float)(2620/1<<FS)*(pow(1.01,((float)selfTest[1] - 1.0) ));
            // FT[Za] factory trim calculation
            factoryTrim[2] = (float)(2620/1<<FS)*(pow(1.01,((float)selfTest[2] - 1.0) ));
            // FT[Xg] factory trim calculation
            factoryTrim[3] = (float)(2620/1<<FS)*(pow(1.01,((float)selfTest[3] - 1.0) ));
            // FT[Yg] factory trim calculation
            factoryTrim[4] = (float)(2620/1<<FS)*(pow(1.01,((float)selfTest[4] - 1.0) ));
            // FT[Zg] factory trim calculation
            factoryTrim[5] = (float)(2620/1<<FS)*(pow(1.01,((float)selfTest[5] - 1.0) ));


            float results[6];

            for (int i = 0; i < 3; i++) {
                // Report percent differences
                results[i] = 100.0 * ((float)(aSTAvg[i] - aAvg[i]))/factoryTrim[i]- 100./*selfTest[i]*/;
                // Report percent differences
                results[i+3] =100.0*((float)(gSTAvg[i] - gAvg[i]))/factoryTrim[i+3]- 100./*selfTest[i+3]*/;
            }
            
            printf("\n\r");
            printf("x-axis self test: acceleration trim within : %f of factory value\r\n", results[0]);
            printf("y-axis self test: acceleration trim within : %f of factory value\r\n", results[1]);
            printf("z-axis self test: acceleration trim within : %f of factory value\r\n", results[2]);
            printf("x-axis self test:     gyration trim within : %f of factory value\r\n", results[3]);
            printf("y-axis self test:     gyration trim within : %f of factory value\r\n", results[4]);
            printf("z-axis self test:     gyration trim within : %f of factory value\r\n", results[5]);

            ICM_20948_D(for (int i = 0; i < 6; i++) {
                ICM_20948_DPRINT("Self Test    Value %d: 0x%x\r\n", i, selfTest[i]);
                ICM_20948_DPRINT("Factory Trim Value %d: %f\r\n", i , factoryTrim[i]);
            });
            ICM_20948_D(
                for (int i = 0; i < 3; i++) {
                    ICM_20948_DPRINT("ACCEL Poll AVG difference [%d]: %d\r\n", i, aSTAvg[i] - aAvg[i]);
                    ICM_20948_DPRINT("ACCEL Poll AVG difference [%d]: %d\r\n", i, gSTAvg[i] - gAvg[i]);
                }
            );
            ICM_20948_D(
                for (int i = 0; i < 3; i++) {
                    ICM_20948_DPRINT("ACCEL Poll AVG without test [%d]: 0x%x\r\n", i, aAvg[i]);
                    ICM_20948_DPRINT("ACCEL Poll AVG with    test [%d]: 0x%x\r\n", i, aSTAvg[i]);
                    ICM_20948_DPRINT("GYRO  Poll AVG without test [%d]: 0x%x\r\n", i, gAvg[i]);
                    ICM_20948_DPRINT("GYRO  Poll AVG with    test [%d]: 0x%x\r\n", i, gSTAvg[i]);
                }
            );
        }
    };
};