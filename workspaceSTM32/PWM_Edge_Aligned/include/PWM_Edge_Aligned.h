//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef PWM_Edge_Aligned_H_
#define PWM_Edge_Aligned_H_

#include "stm32f0xx.h"

/* Define the Timer to be configured */
#define TIMx TIM1
#define TIMx_BASE TIM1_BASE


/* Private function prototypes -----------------------------------------------*/
void ConfigureGPIO(void);
void ConfigureTIMxAsPWM_EdgeAligned(void);
// ----------------------------------------------------------------------------

#endif // PWM_Edge_Aligned_H_
