# Submission Documentation

Something to help understand the thought processes and implementation undertaken for the Technical interview.  

## Assumptions

- Assuming SA1 pulled to ground (Addressing at 0b001110 for sensor)
- Where needed, data is being provided in the correct format to begin with.


## Implementation

This implementation shown within the example can most definelty be improved. Error handling is very minimal and would need to be more robust in production. Increasing the number of error messages would help with extensively with either debugging or dealing with runtime issues.

With new error handling it would also mean that small parts of the code could be rectified during runtime.

## Questions from README

1. For real time operations especially dealing with shared resources like the I2C bus, there should be extra care for locking down with either mutex implementation or if bandwidth allows a semaphor approach. 
    <br>
    The interface should make use of child processes for tasks, This would allow for the main program loop to still function while waiting for a seperate task to finish. 

2. One major feature missing from the I2C driver would be the changes in transfer speed modes especialy as the sensor supports the fast speed configuration. 
    <br>
    To Ensure the that the program doesn't loop forever within the I2C implementation, timeouts should be implemented as to limit the processing power being wasted on sending messages with no answer.
