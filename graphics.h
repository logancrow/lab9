// graphics.h
// LM4F120, TM4C123, TM4C1294
// Simple device driver for the UART.
// Samantha Flaim and Logan Crow
// November 13, 2018

#include <stdint.h>

//initialize LCD graphics display
//clears screen and writes init text
//input: temp (temperature measured by thermister)
//input: ADCString (ADC input)
void Graphics_Init(uint32_t temp, char* ADCString);

//write temperature to screen
void Graphics_WriteTemp(uint32_t temp);