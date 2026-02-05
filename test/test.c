//testing for proper functionality within the operation of the LIS3MDLTR sensor driver.
//Ny no means extensive, just a few tests to show how it could work. These tests will fail without a proper i2c implementation and connection to the sensor.
#include <stdio.h>
#include <stdlib.h>

#include "../src/LIS3MDLTR_Driver.c"

int main(int argc, char const *argv[])
{
    //create an arbitrary buffers for testing
    printf("Starting LIS3MDLTR Driver Tests\n ----------\n");
    
    //Full scale config test
    printf("Full Scale Config Test:\n");
    uint8_t fsBuffer = 0;
    
    full_scale_config_get(&fsBuffer);
    printf("Full Scale Config Value: %d\n", fsBuffer);
    printf("----------\n");
    //Interrupt Set Test
    printf("Interrupt Set Test:\n");
    printf("Interrupt set to 1: %s\n", set_interrupts(1) ? "Failure" : "Success");
    printf("Interrupt set to 0: %s\n", set_interrupts(0) ? "Failure" : "Success");


    printf("----------\n");
    //Output Data Rate Set/Get Test. These fail because of i2c implementation
    //These just show how it could work.
    printf("Output Data Rate Set Test:\n");
    printf("Setting Output Data Rate to 20 Hz\n");
    uint8_t odrBuffer = ODR_20_HZ;
    output_data_rate_set(&odrBuffer);

    printf("----------\n");
    printf("Output Data Rate Get Test:\n");
    output_data_rate_get(&odrBuffer);
    printf("Output Data Rate Value: %d\n", odrBuffer == ODR_20_HZ ? 20 : -1);

    printf("----------\n");
    //Axis data read test
    printf("Axis Data Read Test:\n");

    //allocate memory for axis data
    uint16_t axisData = 0;
    //perfrom actions & print result
    axis_data_read('x', &axisData);
    printf("X-Axis Data Value: %d\n", axisData);

    axis_data_read('y', &axisData);
    printf("Y-Axis Data Value: %d\n", axisData);

    axis_data_read('z', &axisData);
    printf("Z-Axis Data Value: %d\n", axisData);

    printf("----------\n");

    
    return 0;
}
