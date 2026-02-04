//File used to define standard information for the magnetometer pulled from the datasheet.

#define LIS3MDLTR_ADDRESS   (0b001110)
#define REG_Size            (0b1000)

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