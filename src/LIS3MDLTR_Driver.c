#include <i2c.h>
#include <LIS3MDLTR.h>

//temporary buffer for operations on I2C bus
const uint8_t buffer;

//get full-scale configuration of the magnetometer. Outputs the actual value (+-4 -> +-16) not register value.
status_t full_scale_config_get(uint8_t *outputBuffer){
    //full scale config kept within CTRL_REG2 at bits 5 & 6
    uint8_t tempBuffer;
    i2c_read(
        LIS3MDLTR_ADDRESS,
        CTRL_REG2,
        REG_Size,
        &tempBuffer
    );
    
    //extract full scale config bits
    tempBuffer = (tempBuffer & 0b01100000);
    //get actual value and set in output buffer
    *outputBuffer = tempBuffer >> 3;

    return STATUS_OK;
}

//set output data rate
status_t output_data_rate_set(){
    return STATUS_OK;
}

//get output data rate
status_t output_data_rate_get(){
    return STATUS_OK;
}

//get data from user defined axis
status_t axis_data_read(char axis){
    //user sends a character for which axis should be read from.
    //To prevent edge cases, prevent new readings from the magnetometer
    //while reading.

    i2c_write(
        LIS3MDLTR_ADDRESS,
        CTRL_REG5,
        REG_Size,
        &buffer
    );
    //Allocate memory for data and preprocessing
    uint16_t axisData;
    uint8_t lowerDataBits;
    uint8_t upperDataBits;

    switch(axis){
        case 'x':

            break;
        case 'y':

            break;
        case 'z':

            break;
        default:
            printf("Not a real axis");
            return STATUS_ERROR;
    }
}