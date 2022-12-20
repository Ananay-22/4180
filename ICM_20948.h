// include types
// define vec3

class ICM_20948 {
    // constructor should ask which pins and should determine which interface:
    // maybe pass in an SPI/ I2C flag?
    void setBank(); // make sure register maps in bank is properly utilized by this api
    void reset();
    void setPowerMode(); // datasheet 4.22 POWER MODES

    bool isConnected();
    bool isReady();
    bool isICM_20948(); // who am i command matches

    // check sensor modes in documentation
    void lp_config(); // datasheet 8.3 LP_CONFIG
    void setSampleRate(); 


    void read(); void write(); // basic read/ write operations depending on communication protocol used (SPI vs I2C)

    
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
    void enableFIFO();
    void resetFIFO();
    void readFIFO();
    void getFIFOLength();


    // DMP stuff?
    // datasheet section 14.3 specifies to use mutexes in multi threaded env with I2C
    // should make mutexes abstract in read/ write
    void DMPMemoryRead(/*addr*/, /*buffer*/, /*length*/);
    void DMPMemoryWrite(/*addr*/, /*data*/, /*length*/);
    void DMPReset();
    void DMPSetProgram(); // check how to get the processor to load in a program? could not find in datasheet. 
                          // looks similar to goldilox processor in uLCD, in the sense that it can have an independent program without 
                          // the mbed running on this sensor

}