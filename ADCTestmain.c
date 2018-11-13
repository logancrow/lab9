// ADCTestmain.c
// Runs on LM4F120/TM4C123
// Provide a function that initializes Timer0A to trigger ADC
// SS3 conversions and request an interrupt when the conversion
// is complete.
// Daniel Valvano
// May 3, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// center of X-ohm potentiometer connected to PE3/AIN0
// bottom of X-ohm potentiometer connected to ground
// top of X-ohm potentiometer connected to +3.3V through X/10-ohm ohm resistor
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ADCT0ATrigger.h"
#include "PLL.h"
#include "UART.h"
#include "ST7735.h"
#include "calibrate.h"
#include "fixed.h"
#include <stdio.h>

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode


void PortF_Init(){
	GPIO_PORTF_DIR_R |= 0x04;                // make PF2 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x04;             // disable alt funct on PF2
  GPIO_PORTF_DEN_R |= 0x04;                // enable digital I/O on PF2
                                           // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;                  // disable analog functionality on PF
  GPIO_PORTF_DATA_R &= ~0x04;              // turn off LED
}

//debug code
//
// This program periodically samples ADC0 channel 0 and stores the
// result to a global variable that can be accessed with the JTAG
// debugger and viewed with the variable watch feature.


int main(void){
  PLL_Init(Bus80MHz);                      // 80 MHz system clock
  SYSCTL_RCGCGPIO_R |= 0x00000020;         // activate port F
	//Uncomment for procedure 1
  //ADC0_InitTimer0ATriggerSeq3(0, 80000);   // ADC channel 0, 1000 Hz sampling
	ADC0_InitTimer0ATriggerSeq3(0, 800000);    // ADC channel 0, 100 Hz sampling
	UART_Init();
	ST7735_InitR(INITR_REDTAB);
  EnableInterrupts();
  while(1){
		if(ready){
			uint32_t temp = calibrate(ADCIn);
			char* ADCString;
			sprintf(ADCString,"%d",ADCIn);
			ready = 0;
			ST7735_FillScreen(ST7735_BLACK); 
			ST7735_SetCursor(0,0);
			ST7735_OutString("Temperature: ");
			ST7735_sDecOut2(temp);
			ST7735_OutString("\nADC Value: ");
			ST7735_OutString(ADCString);		
		}
		//uncomment for procedure 1
		/*if(count == 99){
			for(int i = 0;i < 100;i++){ 
				UART_OutUDec(dump[i]); 
			} 
		} */
  }
}

