//calibrate.h
//Function declaration for calibrate
//Logan Crow and Samantha Flaim
//Date Created: 11/12/2018
//Last Modified: 11/12/2018

#include <stdint.h>

/****************calibrate***************
 Converts ADC value from 0 to 4096 to Celcius temperature 
 between 10 and 40
 Inputs:  unsigned 12 bit value
 Outputs: Temperature at resolution .01
 */ 
uint32_t calibrate(uint32_t);
