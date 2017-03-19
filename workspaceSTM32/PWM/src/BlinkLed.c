//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "BlinkLed.h"

// ----------------------------------------------------------------------------

void
blink_led_init()
{
  // Enable GPIO Peripheral clock
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  //Andy's attempt at blinking an LED

  //Enable the A port to be used
  RCC->AHBENR |= RCC_AHBPeriph_GPIOC | RCC_AHBPeriph_GPIOA;

  //For now use the GPIO_Init function, to save time
  //Be careful because not erasing any of the past settings so failure to overwrite will keep them

  //Select port 3 to be our toggle port
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET);

  //initialize structs
  GPIO_InitTypeDef LEDs;

  //initialize the PWM out channel
  LEDs.GPIO_Pin = GPIO_Pin_6;
  LEDs.GPIO_Mode = GPIO_Mode_AF;
  LEDs.GPIO_OType = GPIO_OType_PP;
  LEDs.GPIO_PuPd = GPIO_PuPd_NOPULL;
  LEDs.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_Init(GPIOA, &LEDs);


}

// ----------------------------------------------------------------------------
