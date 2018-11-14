//graphics.c
//Function definitions for functions prototyped in graphics.h
//Logan Crow and Samantha Flaim
//Date Created: 11/10/2018
//Last Modified: 11/13/2018

#include "graphics.h"
#include <stdint.h>
#include <stdio.h>
#include "ST7735.h"
#include "fixed.h"

uint32_t j = 0; //keeps counts of the number of data points collected
uint32_t fs = 100; //sample rate = 100Hz
uint32_t N = 50; //100Hz/50 samples plotted per sec

void Graphics_Init(uint32_t temp, char* ADCString) {
	ST7735_FillScreen(ST7735_BLACK); 
	ST7735_SetCursor(0,0);
	ST7735_OutString("Temperature: ");
	ST7735_sDecOut2(temp);
	ST7735_OutString("\nADC Value: ");
	ST7735_OutString(ADCString);		
}

void Graphics_WriteTemp(uint32_t temp) {
	ST7735_SetCursor(0,0);
	ST7735_OutString("Temperature: ");
	ST7735_sDecOut2(temp);
}

void Graphics_PlotInit(void) {
	ST7735_FillScreen(ST7735_BLACK);
	ST7735_SetCursor(0,0);
	ST7735_OutString("Lab 9");
	ST7735_PlotClear(1000,4000);
	ST7735_SetCursor(0,1);
	ST7735_OutString("N=");
	ST7735_SetCursor(0,2);
	ST7735_OutString("T=");
	ST7735_sDecOut2(2500);
	ST7735_OutString(" C");
}

void Graphics_PlotPoint(uint32_t temp, uint32_t data) {
	ST7735_PlotPoint(temp);
	if ((j&(N-1)) == 0) {
		ST7735_PlotNextErase();
	}
	if ((j%fs)==0) {
		ST7735_SetCursor(3,1);
		ST7735_OutUDec(data);
		ST7735_SetCursor(2,2);
		ST7735_sDecOut2(temp);
	}
	j++;
}
