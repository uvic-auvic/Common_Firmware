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

void button_init(void);
void led_init(void);

int main(void){
	button_init();
	led_init();
	int button_pressed = 0;
	while(1){
		if((GPIOA->IDR & 0x1) == 0x1 && button_pressed == 0){
			GPIOC->ODR ^= GPIO_ODR_8;
			button_pressed=1;
		}
		if((GPIOA->IDR & 0x1) == 0x1 && button_pressed == 1){
			button_pressed=0;
		}
	}
}

void button_init(void){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOA;//turns on board section A
	//the button pin (PA0) is set as input by default; therefore,
	//there is no need for a  GPIOA->MODER |= 0x0; statement
}
void led_init(void){
	RCC->AHBENR |= RCC_AHBPeriph_GPIOC;
	GPIOC->MODER |= 0x10000;
}//see blink for explanation
