//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Timer.h"
#include "BlinkLed.h"
#include "stm32f0xx_misc.h"
#include "stm32f0xx_tim.h"
#include <stm32f0xx_rcc.h>
#include "UART.h"
#include "FSM.h"
#include "Buffer.h"
#include "motors.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_syscfg.h"
#include "PWM_in.h"
#include "I2C.h"
#include "temp_sensor.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"


void led_init(void);
//prototype for the LED initialization function written below main

int main(void)
{
	led_init();//calls the led initialization
	int k =0;
	while(1){
		GPIOC->ODR ^= GPIO_ODR_9; //ODR = output data register
		while(k<2000000){
			k++;
		}
		k =0;
	}
}

void led_init(void){
	 RCC->AHBENR |= RCC_AHBPeriph_GPIOC;//turns on board section C
	 /*AHBENR = advanced high speed bus enable register
	 AHBPeriph = advanced high speed bus peripheral,
	 RCC= realtime clock control*/
	 GPIOC->MODER |= 0x40000; //see datasheet page 157
	 /*
	  * we want PC9 to be an output
	  *
	  * according to the datasheet: 01 = general purpose output mode
	  *
	  * also on the datasheet: MODER9 = 19 18 therefore, we want bit 19=0 and bit 18=1
	  * and the rest of the bits=0
	  *
	  * therefore: 				0010 0000 0000 0000 0000
	  * bits:		20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
	  * bits 1-17=0, 18=1, 19=0, and 20=0
	  * note: the additional bit 20 at the end was added because the bits must be divisible
	  * 	  by 4
	  *
	  * to make the code shorter and more readable we convert to hex
	  * hex to binary conversion: 0010 0000 0000 0000 0000
	  *	  	  	                    4    0    0    0    0
	  *	  					            Hex = 0x40000
	  *	  					     (0x indicates the value is in hex
	  *	  					 and 0b indicates that the value is in binary)
	  * 				Note: 0x40000 can also be written as 0b00100000000000000000
	  *
	  * Summary: GPIOC refers to the C section of the board, MODER |= 0x40000 sets MODER bit
	  * 19 to 0 and 18 to 1 resulting PC9 being set to general purpose output mode
	  */

}

