#pragma once

#ifndef __ICM_20948_H__

#include "mbed.h"
#include <stdint.h>
#include "defs.h"
#include "interface.h"

#define ICM_20948_DEBUG 1
#define ICM_20948_D(x) if (ICM_20948_DEBUG) do {x;} while(0)
#define ICM_20948_DPRINT(args...) if (ICM_20948_DEBUG) do {printf(args);fflush(stdout);} while(0);

/*
    Questions for Professor Hamblen:
        1)  How expensive are vectors in this context? Want to implement a Bank Stack -> pushed at 
            the beginning of each every function that writes to a register on the ICM 20948, and
            pops when it returns. If it's too expensive, we can have a 10 elem long array with a 
            pointer that is managed similar to a stack, and will error out and reset the device on
            an overflow. 

            This is to prevent issues where the bank is set by a command and the user thinks they
            are at bank x when the command set them at bank y.
*/

namespace ECE4180{
    typedef uint8_t byte;
    struct vec3 {
        float x;
        float y;
        float z;
    };

    namespace ICM_20948 {

        enum Bank {
            BANK_0 = 0x00,
            BANK_1 = 0x10,
            BANK_2 = 0x20,
            BANK_3 = 0x30
        };

        class ICM_20948 : public I2C
        {
        private:
            Bank currentBank;

            bool __is_IMC_20948_init;
            void __init();
            void __calibrate();

        public:
            ICM_20948(PinName sda, PinName scl);
            // constructor should ask which pins and should determine which interface:
            // maybe pass in an SPI/ I2C flag?
            void setBank(Bank); // make sure register maps in bank is properly utilized by this api
            void setClockDefault();
            void reset();
            void resetDMP();
            void resetFIFO();
            void resetFIFOSize();
            void setFIFOSnapshot();
            void setFIFOStream();
            void setPowerMode(); // datasheet 4.22 POWER MODES

            void disableFIFO();
            void enableFIFO();
            void disableInterrupts();
            void enableInterrupts();

            void disableUserControl();

            void sleep();
            void wakeup();

            void enableTemp();
            void disableTemp();

            //void setClockSource();


            bool isConnected();
            bool isReady();
            bool isICM_20948(); // who am i command matches
            byte whoami();

            // basic read/ write operations depending on communication protocol used (SPI vs I2C)
            void read(BANK_REGISTERS, BANK_DATA&);
            byte read(BANK_REGISTERS);
            byte read(byte);
            void write(BANK_REGISTERS, BANK_DATA);
            void write(BANK_REGISTERS, byte);


            uint32_t agmt;

            void readAGMT();
            float getTemp(); // check units
            vec3 getGyro(); // check units
            vec3 getAcc(); // check units
            vec3 getMag(); // check units


            // interrupts as per datasheet section 5
            void enableInterrupt(/*Interrupt Option*/); // one of 7 options in table 13 in section 5
            // make sure to configure interrupt configurations (read status register etc.) -> read datasheet for more info

            // I2C slave and master configurations as per datasheets section 4.11 and 4.12


            // use fifo buffer? as per section datasheet 4.16
            void readFIFO();
            void getFIFOLength();


            // DMP stuff?
            // datasheet section 14.3 specifies to use mutexes in multi threaded env with I2C
            // should make mutexes abstract in read/ write
            //void DMPMemoryRead(/*addr*/, /*buffer*/, /*length*/);
            //void DMPMemoryWrite(/*addr*/, /*data*/, /*length*/);
            //void DMPReset();
            //void DMPSetProgram(); // check how to get the processor to load in a program? could not find in datasheet.
            // looks similar to goldilox processor in uLCD, in the sense that it can have an independent program without
            // the mbed running on this sensor

        };

        void ICM_20948_selfTest(ICM_20948&);
    };
};

#define __ICM_20948_H__
#endif