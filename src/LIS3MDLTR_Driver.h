//provide name definitions for the LIS3MDLTR
#include "i2c.h"

status_t full_scale_config_get(uint8_t *outputBuffer);
status_t output_data_rate_set(uint8_t *outputBuffer);
status_t output_data_rate_get(uint8_t *outputBuffer);
status_t set_interrupts(int enable);
status_t axis_data_read(char axis, uint16_t *outputData);