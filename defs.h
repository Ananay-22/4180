#define DEG_TO_RAD (1/57.2957795)
#define RAD_TO_DEG 57.2957795

//Magnetometer Registers
#define AK09916_ADDRESS  0x0C 
#define WHO_AM_I_AK09916 0x01 // (AKA WIA2) should return 0x09
#define AK09916_ST1      0x10  // data ready status bit 0
#define AK09916_XOUT_L   0x11  // data
#define AK09916_XOUT_H   0x12
#define AK09916_YOUT_L   0x13
#define AK09916_YOUT_H   0x14
#define AK09916_ZOUT_L   0x15
#define AK09916_ZOUT_H   0x16
#define AK09916_ST2      0x18  // Data overflow bit 3 and data read error status bit 2
#define AK09916_CNTL     0x30  // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
#define AK09916_CNTL2    0x31  // Normal (0), Reset (1)
 
/*
Below were converted to enums using python: 
@author Ananay Gupta
banks = [bank_0, bank_1, bank_2, bank_3]
def process_bank(bank, bank_no):
    kvps = []
    
    for i in bank.split("\n"):
        if i.strip() != "":
            kvps += ((*(i.strip().split()[1:3]), bank_no, *(i.strip().split()[4:])),)
    return kvps
    

for i in range(len(banks)):
    print("enum BANK_" + str(i) + "_REGISTERS {")
    kvps = process_bank(banks[i], i)
    for j in kvps:
        print("\t%30s =%10s, //BANK %d%s" % (j[0], j[1], i, ": " + " ".join(j[3:]) if len(j) > 3 else ""))
        #print("\t", j[0], "=", j[1], ", //BANK",i, ": " + " ".join(j[3:]) if len(j) > 3 else "")
    print("};")
*/    

 
// ICM-20948
enum ICM_20948_BANK_REGISTERS {
                 // BANK 0
                 WHO_AM_I_ICM20948 =      0x00, //BANK 0: Should return 0xEA
                         USER_CTRL =      0x03, //BANK 0: Bit 7 enable DMP, bit 3 reset DMP
                         LP_CONFIG =      0x05, //BANK 0: Not found in MPU-9250
                        PWR_MGMT_1 =      0x06, //BANK 0: Device defaults to the SLEEP mode
                        PWR_MGMT_2 =      0x07, //BANK 0
                       INT_PIN_CFG =      0x0F, //BANK 0
                        INT_ENABLE =      0x10, //BANK 0
                      INT_ENABLE_1 =      0x11, //BANK 0: Not found in MPU-9250
                      INT_ENABLE_2 =      0x12, //BANK 0: Not found in MPU-9250
                      INT_ENABLE_3 =      0x13, //BANK 0: Not found in MPU-9250
                    I2C_MST_STATUS =      0x17, //BANK 0
                        INT_STATUS =      0x19, //BANK 0
                      INT_STATUS_1 =      0x1A, //BANK 0: Not found in MPU-9250
                      INT_STATUS_2 =      0x1B, //BANK 0: Not found in MPU-9250
                      INT_STATUS_3 =      0x1C, //BANK 0: Not found in MPU-9250
                       DELAY_TIMEH =      0x28, //BANK 0: Not found in MPU-9250
                       DELAY_TIMEL =      0x29, //BANK 0: Not found in MPU-9250
                      ACCEL_XOUT_H =      0x2D, //BANK 0
                      ACCEL_XOUT_L =      0x2E, //BANK 0
                      ACCEL_YOUT_H =      0x2F, //BANK 0
                      ACCEL_YOUT_L =      0x30, //BANK 0
                      ACCEL_ZOUT_H =      0x31, //BANK 0
                      ACCEL_ZOUT_L =      0x32, //BANK 0
                       GYRO_XOUT_H =      0x33, //BANK 0
                       GYRO_XOUT_L =      0x34, //BANK 0
                       GYRO_YOUT_H =      0x35, //BANK 0
                       GYRO_YOUT_L =      0x36, //BANK 0
                       GYRO_ZOUT_H =      0x37, //BANK 0
                       GYRO_ZOUT_L =      0x38, //BANK 0
                        TEMP_OUT_H =      0x39, //BANK 0
                        TEMP_OUT_L =      0x3A, //BANK 0
                  EXT_SENS_DATA_00 =      0x3B, //BANK 0
                  EXT_SENS_DATA_01 =      0x3C, //BANK 0
                  EXT_SENS_DATA_02 =      0x3D, //BANK 0
                  EXT_SENS_DATA_03 =      0x3E, //BANK 0
                  EXT_SENS_DATA_04 =      0x3F, //BANK 0
                  EXT_SENS_DATA_05 =      0x40, //BANK 0
                  EXT_SENS_DATA_06 =      0x41, //BANK 0
                  EXT_SENS_DATA_07 =      0x42, //BANK 0
                  EXT_SENS_DATA_08 =      0x43, //BANK 0
                  EXT_SENS_DATA_09 =      0x44, //BANK 0
                  EXT_SENS_DATA_10 =      0x45, //BANK 0
                  EXT_SENS_DATA_11 =      0x46, //BANK 0
                  EXT_SENS_DATA_12 =      0x47, //BANK 0
                  EXT_SENS_DATA_13 =      0x48, //BANK 0
                  EXT_SENS_DATA_14 =      0x49, //BANK 0
                  EXT_SENS_DATA_15 =      0x4A, //BANK 0
                  EXT_SENS_DATA_16 =      0x4B, //BANK 0
                  EXT_SENS_DATA_17 =      0x4C, //BANK 0
                  EXT_SENS_DATA_18 =      0x4D, //BANK 0
                  EXT_SENS_DATA_19 =      0x4E, //BANK 0
                  EXT_SENS_DATA_20 =      0x4F, //BANK 0
                  EXT_SENS_DATA_21 =      0x50, //BANK 0
                  EXT_SENS_DATA_22 =      0x51, //BANK 0
                  EXT_SENS_DATA_23 =      0x52, //BANK 0
                         FIFO_EN_1 =      0x66, //BANK 0
                         FIFO_EN_2 =      0x67, //BANK 0: Not found in MPU-9250
                          FIFO_RST =      0x68, //BANK 0: Not found in MPU-9250
                         FIFO_MODE =      0x69, //BANK 0: Not found in MPU-9250
                       FIFO_COUNTH =      0x70, //BANK 0
                       FIFO_COUNTL =      0x71, //BANK 0
                          FIFO_R_W =      0x72, //BANK 0
                   DATA_RDY_STATUS =      0x74, //BANK 0: Not found in MPU-9250
                          FIFO_CFG =      0x76, //BANK 0: Not found in MPU-9250
                      REG_BANK_SEL =      0x7F, //BANK 0: Not found in MPU-9250
                // BANK 1
                  SELF_TEST_X_GYRO =      0x02, //BANK 1
                  SELF_TEST_Y_GYRO =      0x03, //BANK 1
                  SELF_TEST_Z_GYRO =      0x04, //BANK 1
                 SELF_TEST_X_ACCEL =      0x0E, //BANK 1
                 SELF_TEST_Y_ACCEL =      0x0F, //BANK 1
                 SELF_TEST_Z_ACCEL =      0x10, //BANK 1
                       XA_OFFSET_H =      0x14, //BANK 1
                       XA_OFFSET_L =      0x15, //BANK 1
                       YA_OFFSET_H =      0x17, //BANK 1
                       YA_OFFSET_L =      0x18, //BANK 1
                       ZA_OFFSET_H =      0x1A, //BANK 1
                       ZA_OFFSET_L =      0x1B, //BANK 1
           TIMEBASE_CORRECTION_PLL =      0x28, //BANK 1
            // BANK 2
                   GYRO_SMPLRT_DIV =      0x00, //BANK 2: Not found in MPU-9250
                     GYRO_CONFIG_1 =      0x01, //BANK 2: Not found in MPU-9250
                     GYRO_CONFIG_2 =      0x02, //BANK 2: Not found in MPU-9250
                       XG_OFFSET_H =      0x03, //BANK 2: User-defined trim values for gyroscope
                       XG_OFFSET_L =      0x04, //BANK 2
YG_OFFSET_H =      0x05, //BANK 2
                       YG_OFFSET_L =      0x06, //BANK 2
                       ZG_OFFSET_H =      0x07, //BANK 2
                       ZG_OFFSET_L =      0x08, //BANK 2
                      ODR_ALIGN_EN =      0x09, //BANK 2: Not found in MPU-9250
                ACCEL_SMPLRT_DIV_1 =      0x10, //BANK 2: Not found in MPU-9250
                ACCEL_SMPLRT_DIV_2 =      0x11, //BANK 2: Not found in MPU-9250
                  ACCEL_INTEL_CTRL =      0x12, //BANK 2: Not found in MPU-9250
                     ACCEL_WOM_THR =      0x13, //BANK 2: Not found in MPU-9250 (could be WOM_THR)
                      ACCEL_CONFIG =      0x14, //BANK 2
                    ACCEL_CONFIG_2 =      0x15, //BANK 2: Not found in MPU-9250 (could be ACCEL_CONFIG2)
                      FSYNC_CONFIG =      0x52, //BANK 2: Not found in MPU-9250
                       TEMP_CONFIG =      0x53, //BANK 2: Not found in MPU-9250
                      MOD_CTRL_USR =      0x54, //BANK 2: Not found in MPU-9250
                // BANK 3
                I2C_MST_ODR_CONFIG =      0x00, //BANK 3: Not found in MPU-9250
                      I2C_MST_CTRL =      0x01, //BANK 3
                I2C_MST_DELAY_CTRL =      0x02, //BANK 3
                     I2C_SLV0_ADDR =      0x03, //BANK 3
                      I2C_SLV0_REG =      0x04, //BANK 3
                     I2C_SLV0_CTRL =      0x05, //BANK 3
                       I2C_SLV0_DO =      0x06, //BANK 3
                     I2C_SLV1_ADDR =      0x07, //BANK 3
                      I2C_SLV1_REG =      0x08, //BANK 3
                     I2C_SLV1_CTRL =      0x09, //BANK 3
                       I2C_SLV1_DO =      0x0A, //BANK 3
                     I2C_SLV2_ADDR =      0x0B, //BANK 3
                      I2C_SLV2_REG =      0x0C, //BANK 3
                     I2C_SLV2_CTRL =      0x0D, //BANK 3
                       I2C_SLV2_DO =      0x0E, //BANK 3
                     I2C_SLV3_ADDR =      0x0F, //BANK 3
                      I2C_SLV3_REG =      0x10, //BANK 3
                     I2C_SLV3_CTRL =      0x11, //BANK 3
                       I2C_SLV3_DO =      0x12, //BANK 3
                     I2C_SLV4_ADDR =      0x13, //BANK 3
                      I2C_SLV4_REG =      0x14, //BANK 3
                     I2C_SLV4_CTRL =      0x15, //BANK 3
                       I2C_SLV4_DO =      0x16, //BANK 3
                       I2C_SLV4_DI =      0x17, //BANK 3
};
 
// Using the ICM-20948 breakout board, ADO is set to 1
// Seven-bit device address is 1000100 for ADO = 0 and 1000101 for ADO = 1
#define ADO 0 
#if ADO
#define ICM20948_ADDRESS 0x69<<1  // Device address when ADO = 1
#else
#define ICM20948_ADDRESS 0x68<<1  // Device address when ADO = 0
#define AK09916_ADDRESS  0x0C   // Address of magnetometer
#endif // AD0
 
#define READ_FLAGS 0x80