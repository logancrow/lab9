//calibrate.c
//Function definitions for functions prototyped in calibrate.h
//Logan Crow and Samantha Flaim
//Date Created: 11/12/2018
//Last Modified: 11/12/2018

#include <stdint.h>
#include "calibrate.h"
#include <math.h>

/****************calibrate***************
 Converts ADC value from 0 to 4096 to Celcius temperature 
 between 10 and 40
 Inputs:  unsigned 12 bit value
 Outputs: Temperature at resolution .01
 */ 
uint32_t calibrate(uint32_t ADC_In){
	uint32_t converted = 3951 - ((5*ADC_In*ADC_In)/10000) - ((ADC_In*4053)/10000);
	return converted;
}
