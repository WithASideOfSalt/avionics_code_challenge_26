//File used to define standard information for the magnetometer pulled from the datasheet.

#define LIS3MDLTR_ADDRESS   (0b001110)
#define REG_SIZE            (1)

//Control Registers

#define CTRL_REG1           (0b00100000)
#define CTRL_REG2           (0b00100001)
#define CTRL_REG3           (0b00100010)
#define CTRL_REG4           (0b00100011)
#define CTRL_REG5           (0b00100100)

//Data Registers

#define X_REG_L_M           (0b00000101)
#define X_REG_H_M           (0b00000110)
#define Y_REG_L_M           (0b00000111)
#define Y_REG_H_M           (0b00001000)
#define Z_REG_L_M           (0b00001001)
#define Z_REG_H_M           (0b00001010)
#define INT_CFG_M           (0b00110000)

//ODR Values

#define ODR_0_625_HZ        (0b00000000)
#define ODR_1_25_HZ         (0b00000100)
#define ODR_2_5_HZ          (0b00001000)
#define ODR_5_HZ            (0b00001100)
#define ODR_10_HZ           (0b00010000)
#define ODR_20_HZ           (0b00010100)
#define ODR_40_HZ           (0b00011000)
#define ODR_80_HZ           (0b00011100)