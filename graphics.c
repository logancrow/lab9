//graphics.c
//Function definitions for functions prototyped in graphics.h
//Logan Crow and Samantha Flaim
//Date Created: 11/10/2018
//Last Modified: 11/13/2018

#include <stdint.h>
#include <stdio.h>
#include "ST7735.h"

void Graphics_Init(uint32_t temp, char* ADCString) {
	ST7735_FillScreen(ST7735_BLACK); 
	ST7735_SetCursor(0,0);
	ST7735_OutString("Temperature: ");
	ST7735_DecOut(temp);
	ST7735_OutString("\nADC Value: ");
	ST7735_OutString(ADCString);		
}

void Graphics_WriteTemp(uint32_t temp) {
	ST7735_SetCursor(0,0);
	ST7735_OutString("Temperature: ");
	ST7735_DecOut(temp);
}

void Graphics_Plot() {
	
}