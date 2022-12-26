#pragma once

#ifndef __INTERFACE_H__
namespace ECE4180 {
    typedef unsigned char bits_t;
    namespace ICM_20948 {
        union BANK_DATA {
            // BANK 0
            struct {
                bits_t WHO_AM_I                     : 8; // BITS 0:8
            } WHO_AM_I;
            struct {
                bits_t _                            : 1; // BIT  0
                bits_t I2C_MST_RST                  : 1; // BIT  1
                bits_t SRAM_RST                     : 1; // BIT  2
                bits_t DMP_RST                      : 1; // BIT  3
                bits_t I2C_IF_DIS                   : 1; // BIT  4
                bits_t I2C_MST_EN                   : 1; // BIT  5
                bits_t FIFO_EN                      : 1; // BIT  6
                bits_t DMP_EN                       : 1; // BIT  7
            } USER_CTRL;
            struct {
                bits_t _                            : 4; // BITS 0:3
                bits_t GYRO_CYCLE                   : 1; // BIT  5
                bits_t ACCEL_CYCLE                  : 1; // BIT  6
                bits_t I2C_MST_CYCLE                : 1; // BIT  7
                bits_t __                           : 1; // BIT  8
            } LP_CONFIG;
            struct {
                bits_t CLKSEL                       : 3; // BITS 0:2
                bits_t TEMP_DIS                     : 1; // BIT  3
                bits_t _                            : 1; // BIT  4
                bits_t LP_EN                        : 1; // BIT  5
                bits_t SLEEP                        : 1; // BIT  6
                bits_t DEVICE_RESET                 : 1; // BIT  7
            } PWR_MGMT_1;
            struct {
                bits_t DISABLE_GYRO                 : 3; // BITS 0:2
                bits_t DISABLE_ACCEL                : 3; // BITS 3:5
                bits_t _                            : 2; // BITS 6:7
            } PWR_MGMT_2;
            struct {
                bits_t _                            : 1; // BIT  0
                bits_t BYPASS_EN                    : 1; // BIT  1
                bits_t FSYNC_INT_MODE_EN            : 1; // BIT  2
                bits_t ACTL_FSYNC                   : 1; // BIT  3
                bits_t INT_ANYRD_2CLEAR             : 1; // BIT  4
                bits_t INT1_LATCH_INT_EN            : 1; // BIT  5
                bits_t INT1_OPEN                    : 1; // BIT  6
                bits_t INT1_ACTL                    : 1; // BIT  7
            } INT_PIN_CFG;
            struct {
                bits_t I2C_MST_INT_EN               : 1; // BIT  0
                bits_t DMP_INT1_EN                  : 1; // BIT  1
                bits_t PLL_RDY_EN                   : 1; // BIT  2
                bits_t WOM_INT_EN                   : 1; // BIT  3
                bits_t _                            : 3; // BITS 4:6
                bits_t REG_WOF_EN                   : 1; // BIT  7
            } INT_ENABLE;
            struct {
                bits_t RAW_DATA_0_RDY_EN            : 1; // BIT  0
                bits_t _                            : 7; // BITS 2:7
            } INT_ENABLE_1;
            struct {
                bits_t FIFO_OVERFLOW_EN             : 5; // BITS 0:4
                bits_t _                            : 3; // BITS 5:7
            } INT_ENABLE_2;
            struct {
                bits_t FIFO_WM_EN                   : 5; // BITS 0:4
                bits_t _                            : 3; // BITS 5:7
            } INT_ENABLE_3;
            struct {
                bits_t I2C_SLV0_NACK                : 1; // BIT  0
                bits_t I2C_SLV1_NACK                : 1; // BIT  1
                bits_t I2C_SLV2_NACK                : 1; // BIT  2
                bits_t I2C_SLV3_NACK                : 1; // BIT  3
                bits_t I2C_SLV4_NACK                : 1; // BIT  4
                bits_t I2C_LOST_ARB                 : 1; // BIT  5
                bits_t I2C_SLV4_DONE                : 1; // BIT  6
                bits_t PASS_THROUGH                 : 1; // BIT  7
            } I2C_MST_STATUS;
            struct {
                bits_t I2C_MST_INT                  : 1; // BIT  0
                bits_t DMP_INT1                     : 1; // BIT  1
                bits_t PLL_RDY_INT                  : 1; // BIT  2
                bits_t WOM_INT                      : 1; // BIT  3
                bits_t _                            : 1; // BITS 4:7
            } INT_STATUS;
            struct {
                bits_t RAW_DATA_0_RDY_INT           : 1; // BIT  0
                bits_t _                            : 7; // BITS 2:7
            } INT_STATUS_1;
            struct {
                bits_t FIFO_OVERFLOW_INT            : 5; // BITS 0:4
                bits_t _                            : 3; // BITS 5:7
            } INT_STATUS_2;
            struct {
                bits_t FIFO_WM_INT                  : 5; // BITS 0:4
                bits_t _                            : 3; // BITS 5:7
            } INT_STATUS_3;
            struct {
                bits_t DELAY_TIMEH                  : 8; // BITS 0:8
            } DELAY_TIMEH;
            struct {
                bits_t DELAY_TIMEL                  : 8; // BITS 0:8
            } DELAY_TIMEL;
            // struct {
            //     bits_t DELAY_TIMEH                  : 8; // BITS 0:8
            // } DELAY_TIMEH;
            struct {
                bits_t ACCEL_XOUT_H                 : 8; // BITS 0:8
            } ACCEL_XOUT_H;
            struct {
                bits_t ACCEL_XOUT_L                 : 8; // BITS 0:8
            } ACCEL_XOUT_L;
            struct {
                bits_t ACCEL_YOUT_H                 : 8; // BITS 0:8
            } ACCEL_YOUT_H;
            struct {
                bits_t ACCEL_YOUT_L                 : 8; // BITS 0:8
            } ACCEL_YOUT_L;
            struct {
                bits_t ACCEL_ZOUT_H                 : 8; // BITS 0:8
            } ACCEL_ZOUT_H;
            struct {
                bits_t ACCEL_ZOUT_L                 : 8; // BITS 0:8
            } ACCEL_ZOUT_L;
            struct {
                bits_t GYRO_XOUT_H                  : 8; // BITS 0:8
            } GYRO_XOUT_H;
            struct {
                bits_t GYRO_XOUT_L                  : 8; // BITS 0:8
            } GYRO_XOUT_L;
            struct {
                bits_t GYRO_YOUT_H                  : 8; // BITS 0:8
            } GYRO_YOUT_H;
            struct {
                bits_t GYRO_YOUT_L                  : 8; // BITS 0:8
            } GYRO_YOUT_L;
            struct {
                bits_t GYRO_ZOUT_H                  : 8; // BITS 0:8
            } GYRO_ZOUT_H;
            struct {
                bits_t GYRO_ZOUT_L                  : 8; // BITS 0:8
            } GYRO_ZOUT_L;
            struct {
                bits_t TEMP_OUT_H                   : 8; // BITS 0:8
            } TEMP_OUT_H;
            struct {
                bits_t TEMP_OUT_L                   : 8; // BITS 0:8
            } TEMP_OUT_L;
            struct {
                bits_t EXT_SLV_SENS_DATA_00         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_00;
            struct {
                bits_t EXT_SLV_SENS_DATA_01         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_01;
            struct {
                bits_t EXT_SLV_SENS_DATA_02         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_02;
            struct {
                bits_t EXT_SLV_SENS_DATA_03         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_03;
            struct {
                bits_t EXT_SLV_SENS_DATA_04         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_04;
            struct {
                bits_t EXT_SLV_SENS_DATA_05         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_05;
            struct {
                bits_t EXT_SLV_SENS_DATA_06         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_06;
            struct {
                bits_t EXT_SLV_SENS_DATA_07         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_07;
            struct {
                bits_t EXT_SLV_SENS_DATA_08         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_08;
            struct {
                bits_t EXT_SLV_SENS_DATA_09         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_09;
            struct {
                bits_t EXT_SLV_SENS_DATA_10         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_10;
            struct {
                bits_t EXT_SLV_SENS_DATA_11         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_11;
            struct {
                bits_t EXT_SLV_SENS_DATA_12         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_12;
            struct {
                bits_t EXT_SLV_SENS_DATA_13         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_13;
            struct {
                bits_t EXT_SLV_SENS_DATA_14         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_14;
            struct {
                bits_t EXT_SLV_SENS_DATA_15         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_15;
            struct {
                bits_t EXT_SLV_SENS_DATA_16         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_16;
            struct {
                bits_t EXT_SLV_SENS_DATA_17         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_17;
            struct {
                bits_t EXT_SLV_SENS_DATA_18         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_18;
            struct {
                bits_t EXT_SLV_SENS_DATA_19         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_19;
            struct {
                bits_t EXT_SLV_SENS_DATA_20         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_20;
            struct {
                bits_t EXT_SLV_SENS_DATA_21         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_21;
            struct {
                bits_t EXT_SLV_SENS_DATA_22         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_22;
            struct {
                bits_t EXT_SLV_SENS_DATA_23         : 8; // BITS 0:8
            } EXT_SLV_SENS_DATA_23;
            struct {
                bits_t SLV_0_FIFO_EN                : 1; // BIT  0
                bits_t SLV_1_FIFO_EN                : 1; // BIT  1
                bits_t SLV_2_FIFO_EN                : 1; // BIT  2
                bits_t SLV_3_FIFO_EN                : 1; // BIT  3
                bits_t _                            : 4; // BITS 4:7
            } FIFO_EN_1;
            struct {
                bits_t TEMP_FIFO_EN                 : 1; // BIT  0
                bits_t GYRO_X_FIFO_EN               : 1; // BIT  1
                bits_t GYRO_Y_FIFO_EN               : 1; // BIT  2
                bits_t GYRO_Z_FIFO_EN               : 1; // BIT  3
                bits_t ACCEL_FIFO_EN                : 1; // BIT  4
                bits_t _                            : 4; // BITS 5:7
            } FIFO_EN_2;
            struct {
                bits_t FIFO_RESET                   : 5; // BITS 0:4
                bits_t _                            : 3; // BITS 5:7
            } FIFO_RST;
            struct {
                bits_t FIFO_MODE                    : 5; // BITS 0:4
                bits_t _                            : 3; // BITS 5:7
            } FIFO_MODE;
            struct {
                bits_t FIFO_COUNTH                  : 5; // BITS 0:4
                bits_t _                            : 3; // BITS 5:7
            } FIFO_COUNTH;
            struct {
                bits_t FIFO_COUNTL                  : 8; // BITS 0:8
            } FIFO_COUNTL;
            struct {
                bits_t FIFO_R_W                     : 8; // BITS 0:8
            } FIFO_R_W;
            struct {
                bits_t RAW_DATA_RDY                 : 4; // BITS 0:3
                bits_t _                            : 3; // BITS 4:5
                bits_t WOF_STATUS                   : 1; // BIT  7
            } DATA_RDY_STATUS;
            struct {
                bits_t FIFO_CFG                    : 1; // BIT  0
                bits_t _                           : 7; // BITS 1:7
            } FIFO_CFG;
            struct {
                bits_t _                            : 4; // BITS 0:3
                bits_t USER_BANK                    : 2; // BIT  4:5
                bits_t __                           : 2; // BITS 6:7
            } REG_BANK_SEL;

            // BANK 1
            struct {
                bits_t XG_ST_DATA                   : 8; // BITS 0:7
            } SELF_TEST_X_GYRO;
            struct {
                bits_t YG_ST_DATA                   : 8; // BITS 0:7
            } SELF_TEST_Y_GYRO;
            struct {
                bits_t ZG_ST_DATA                   : 8; // BITS 0:7
            } SELF_TEST_Z_GYRO;
            struct {
                bits_t XA_ST_DATA                   : 8; // BITS 0:7
            } SELF_TEST_X_ACCEL;
            struct {
                bits_t YA_ST_DATA                   : 8; // BITS 0:7
            } SELF_TEST_Y_ACCEL;
            struct {
                bits_t ZA_ST_DATA                   : 8; // BITS 0:7
            } SELF_TEST_Z_ACCEL;
            struct {
                bits_t XA_OFFS_H                    : 8; // BITS 0:7
            } XA_OFFS_H;
            struct {
                bits_t _                            : 1; // BIT  0
                bits_t XA_OFFS_L                    : 7; // BITS 1:7
            } XA_OFFS_L;
            struct {
                bits_t YA_OFFS_H                    : 8; // BITS 0:7
            } YA_OFFS_H;
            struct {
                bits_t _                            : 1; // BIT  0
                bits_t YA_OFFS_L                    : 7; // BITS 1:7
            } YA_OFFS_L;
            struct {
                bits_t ZA_OFFS_H                    : 8; // BITS 0:7
            } ZA_OFFS_H;
            struct {
                bits_t _                            : 1; // BIT  0
                bits_t ZA_OFFS_L                    : 7; // BITS 1:7
            } ZA_OFFS_L;
            struct {
                bits_t TIMEBASE_CORRECTION_PLL      : 8; // BITS 0:7
            } TIMEBASE_CORRECTION_PLL;

            // BANK 2
            struct {
                bits_t GYRO_SMPLRT_DIV              : 8; // BITS 0:7
            } GYRO_SMPLRT_DIV;
            struct {
                bits_t GYRO_FCHOICE                 : 1; // BIT  0
                bits_t GYRO_FS_SEL                  : 2; // BITS 1:2
                bits_t GYRO_DLPFCFG                 : 3; // BITS 3:5
                bits_t _                            : 2; // BIT  6:7
            } GYRO_CONFIG_1;
            struct {
                bits_t GYRO_AVGCFG                  : 3; // BITS 0:2
                bits_t ZGYRO_CTEN                   : 1; // BIT  3
                bits_t YGYRO_CTEN                   : 1; // BIT  4
                bits_t XGYRO_CTEN                   : 1; // BIT  5
                bits_t _                            : 2; // BITS 6:7
            } GYRO_CONFIG_2;
            struct {
                bits_t X_OFFS_USER                  : 8; // BITS 0:7
            } XG_OFFS_USRH;
            struct {
                bits_t X_OFFS_USER                  : 8; // BITS 0:7
            } XG_OFFS_USRL;
            struct {
                bits_t Y_OFFS_USER                  : 8; // BITS 0:7
            } YG_OFFS_USRH;
            struct {
                bits_t Y_OFFS_USER                  : 8; // BITS 0:7
            } YG_OFFS_USRL;
            struct {
                bits_t Z_OFFS_USER                  : 8; // BITS 0:7
            } ZG_OFFS_USRH;
            struct {
                bits_t Z_OFFS_USER                  : 8; // BITS 0:7
            } ZG_OFFS_USRL;
            struct {
                bits_t ODR_ALIGN_EN                 : 1; // BIT  0
                bits_t _                            : 7; // BITS 1:7
            } ODR_ALIGN_EN;
            struct {
                bits_t ACCEL_SMPLRT_DIV             : 4; // BIT  0
                bits_t _                            : 4; // BITS 1:7
            } ACCEL_SMPLRT_DIV_1;
            struct {
                bits_t ACCEL_SMPLRT_DIV             : 8; // BITS 0:7
            } ACCEL_SMPLRT_DIV_2;
            struct {
                bits_t ACCEL_INTEL_MODE_INT         : 1; // BIT  0
                bits_t ACCEL_INTEL_EN               : 1; // BIT  1
                bits_t _                            : 6; // BITS 2:7
            } ACCEL_INTEL_CTRL;
            struct {
                bits_t ACCEL_FCHOICE                : 1; // BIT  0
                bits_t ACCEL_FS_SEL                 : 2; // BITS 1:2
                bits_t ACCEL_DLPFCFG                : 3; // BITS 3:5
                bits_t _                            : 2; // BITS 6:7
            } ACCEL_CONFIG;
            struct {
                bits_t DEC3_CFG                     : 2; // BIT  0:1
                bits_t AZ_ST_EN_REG                 : 1; // BITS 2
                bits_t AY_ST_EN_REG                 : 1; // BITS 3
                bits_t AX_ST_EN_REG                 : 1; // BITS 4
                bits_t _                            : 3; // BITS 5:7
            } ACCEL_CONFIG_2;
            struct {
                bits_t EXT_SYNC_SET                 : 4; // BITS 0:3
                bits_t WOF_EDGE_INT                 : 1; // BIT  4
                bits_t WOF_DEGLITCH_EN              : 1; // BIT  5
                bits_t _                            : 1; // BIT  6
                bits_t DELAY_TIME_EN                : 1; // BIT  7
            } FSYNC_CONFIG;
            struct {
                bits_t TEMP_DLPFCFG                 : 3; // BITS 0:2
                bits_t _                            : 6; // BITS 3:7
            } TEMP_CONFIG;
            // struct {
            //     bits_t REG_LP_DMP_EN                : 1; // BIT  0
            //     bits_t _                            : 7; // BITS 1:7
            // } TEMP_CONFIG;

            // BANK 3
            // TODO: BANK 3













            struct {
                bits_t x0                           : 1; // BIT  0
                bits_t x1                           : 1; // BIT  1
                bits_t x2                           : 1; // BIT  2
                bits_t x3                           : 1; // BIT  3
                bits_t x4                           : 1; // BIT  4
                bits_t x5                           : 1; // BIT  5
                bits_t x6                           : 1; // BIT  6
                bits_t x7                           : 1; // BIT  7
            } _layout;
            unsigned char RAW;
        };
    };
};

#define __INTERFACE_H__
#endif