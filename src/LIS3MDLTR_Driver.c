#include <stdio.h>
#include <stdlib.h>

#include "LIS3MDLTR.h"
#include "LIS3MDLTR_Driver.h"
#include "i2c.c"

//get full-scale configuration of the magnetometer. Outputs the actual value (+-4 -> +-16) not register value.
status_t full_scale_config_get(uint8_t *outputBuffer){
    //full scale config kept within CTRL_REG2 at bits 5 & 6
    if (i2c_read(
        LIS3MDLTR_ADDRESS,
        CTRL_REG2,
        REG_SIZE,
        outputBuffer
    ) == STATUS_ERROR) return STATUS_ERROR;
    
    *outputBuffer = (*outputBuffer & 0b01100000);
    //get actual value corresponding to table in datasheet.
    *outputBuffer = *outputBuffer >> 3;

    return STATUS_OK;
}

//set output data rate
//Assume values are in register place ie. bits 2 -> 4
//Assuming the binary value is the output
status_t output_data_rate_set(uint8_t *inputBuffer){
    //need to allocate a buffer to read current register value
    //don't want to overwrite other bits in the register
    uint8_t buffer = 0;

    output_data_rate_get(&buffer);
    buffer &= 0b11100011;   //Clear bits 2-4 for output data rate selection
   
    //Set values from input buffer
    buffer |= *inputBuffer;
    //Write new value to register
    if (i2c_write(
        LIS3MDLTR_ADDRESS,
        CTRL_REG1,
        REG_SIZE,
        &buffer
    ) == STATUS_ERROR) return STATUS_ERROR;

    return STATUS_OK;
}
//get output data rate
status_t output_data_rate_get(uint8_t* outputBuffer){
    //simply read value of CTRL_REG1
    if (i2c_read(
        LIS3MDLTR_ADDRESS,
        CTRL_REG1,
        REG_SIZE,
        outputBuffer
    ) == STATUS_ERROR) return STATUS_ERROR;
    //Mask other bits out and shift
    *outputBuffer = *outputBuffer & 0b00011100;
    return STATUS_OK;
}

status_t set_interrupts(int enable){
    //sets the interrupt configuration register specifically the IEN bit.
    //Further configuration can be made for interrupts on each axis.
    uint8_t buffer = 0;
    if (i2c_read(
        LIS3MDLTR_ADDRESS,
        INT_CFG_M,
        REG_SIZE,
        &buffer
    ) == STATUS_ERROR) return STATUS_ERROR;

    //set or clear IEN bit of register will preserve other bits.
    if(enable){
        buffer |= 0b00000001;
    } 
    else {
        buffer &= ~0b00000001;
    }

    if (i2c_write(
        LIS3MDLTR_ADDRESS,
        INT_CFG_M,
        REG_SIZE,
        &buffer
    ) == STATUS_ERROR) return STATUS_ERROR;

    return STATUS_OK;
}

//get data from user defined axis
status_t axis_data_read(char axis, uint16_t* outputData){
    //user sends a character for which axis should be read from.
    //To prevent edge cases, prevent new readings from the magnetometer
    //while reading.
    uint8_t buffer = 0;

    //blocking new magnetic data during operation
    if (i2c_read(
        LIS3MDLTR_ADDRESS,
        CTRL_REG5,
        REG_SIZE,
        &buffer
    ) == STATUS_ERROR) return STATUS_ERROR;

    buffer |= 0b01000000;
    
    if (i2c_write(
        LIS3MDLTR_ADDRESS,
        CTRL_REG5,
        REG_SIZE,
        &buffer
    ) == STATUS_ERROR) return STATUS_ERROR;

    //start reading operation

    switch(axis){
        case 'x':
            printf("Reading X-Axis Data\n");
            //read lower and upper registers for x-axis
            if (i2c_read(
                LIS3MDLTR_ADDRESS,
                X_REG_L_M,
                REG_SIZE,
                (uint8_t*)outputData
            ) == STATUS_ERROR) return STATUS_ERROR;

            if (i2c_read(
                LIS3MDLTR_ADDRESS,
                X_REG_H_M,
                REG_SIZE,
                ((uint8_t*)outputData)+1
            ) == STATUS_ERROR) return STATUS_ERROR;
            break;
        case 'y':
            printf("Reading Y-Axis Data\n");
            //read lower and upper registers for y-axis
            if (i2c_read(
                LIS3MDLTR_ADDRESS,
                Y_REG_L_M,
                REG_SIZE,
                (uint8_t*)outputData
            ) == STATUS_ERROR) return STATUS_ERROR;
            
            if (i2c_read(
                LIS3MDLTR_ADDRESS,
                Y_REG_H_M,
                REG_SIZE,
                ((uint8_t*)outputData)+1
            ) == STATUS_ERROR) return STATUS_ERROR;
            break;
        case 'z':
            printf("Reading Z-Axis Data\n");
            if (i2c_read(
                LIS3MDLTR_ADDRESS,
                Z_REG_L_M,
                REG_SIZE,
                (uint8_t*)outputData
            ) == STATUS_ERROR) return STATUS_ERROR;
            
            if (i2c_read(
                LIS3MDLTR_ADDRESS,
                Z_REG_H_M,
                REG_SIZE,
                ((uint8_t*)outputData)+1
            ) == STATUS_ERROR) return STATUS_ERROR;
            break;
        default:
            printf("Not a real axis");
            return STATUS_ERROR;
    }

    //unblock new magnetic data after read operation
    if (i2c_read(
        LIS3MDLTR_ADDRESS,
        CTRL_REG5,
        REG_SIZE,
        &buffer
    ) == STATUS_ERROR) return STATUS_ERROR;
    buffer &= ~0b01000000;
    if (i2c_write(
        LIS3MDLTR_ADDRESS,
        CTRL_REG5,
        REG_SIZE,
        &buffer
    ) == STATUS_ERROR) return STATUS_ERROR;
    return STATUS_OK;
}