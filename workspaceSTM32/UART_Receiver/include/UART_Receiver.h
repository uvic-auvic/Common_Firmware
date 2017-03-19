//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef UART_Receiver_H_
#define UART_Receiver_H_

#include "stm32f0xx.h"

/* Private function prototypes -----------------------------------------------*/
void Configure_GPIO_LED(void);
void Configure_GPIO_USART1(void);
void Configure_USART1(void);
void Configure_GPIO_Button(void);
void Configure_EXTI(void);
// ----------------------------------------------------------------------------

#endif // UART_Receiver_H_
