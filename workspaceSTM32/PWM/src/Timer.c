//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "Timer.h"
#include "cortexm/ExceptionHandlers.h"
#include "stm32f0xx.h"
#include "stm32f0xx_misc.h"

// ----------------------------------------------------------------------------

#if defined(USE_HAL_DRIVER)
void HAL_IncTick(void);
#endif

// Forward declarations.

void
timer_tick (void);

// ----------------------------------------------------------------------------

volatile timer_ticks_t timer_delayCount;

// ----------------------------------------------------------------------------

void
timer_start (void)
{
  // Use SysTick as reference for the delay loops.
  SysTick_Config (SystemCoreClock / TIMER_FREQUENCY_HZ);
}

void timer3_it_config(void){
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 500 - 1; // 48kHz down to 1kHz (1 ms)
	TIM_TimeBaseStructure.TIM_Prescaler = 100 - 1; // 48 MHz Clock down to 480 kHz (adjust per your clock)
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_OCInitTypeDef outputChannelInit = {0,};
	outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
	outputChannelInit.TIM_Pulse = 100-1; //20%
	outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
	outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;

	//Submitting the code for register changes
	TIM_OC1Init(TIM3, &outputChannelInit);
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_1);

	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

void timer1_IT_config(void){
	  GPIO_InitTypeDef GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	  /* GPIOC clock enable */
	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	  /* TIM2 clock enable */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	  /* GPIOA Configuration: TIM2 CH1 (PA0) */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // Input/Output controlled by peripheral
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // Button to ground expectation
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	    /* Connect TIM2 pins to AF */
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);

	  TIM_TimeBaseStructure.TIM_Period = 50000-1;
	  TIM_TimeBaseStructure.TIM_Prescaler = 10-1;
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	  /* (1) Select the active input TI1 (CC1S = 01),
	  program the input filter for 8 clock cycles (IC1F = 0011),
	  select the rising edge on CC1 (CC1P = 0, reset value)
	  and prescaler at each valid transition (IC1PS = 00, reset value) */
	  /* (2) Enable capture by setting CC1E */
	  /* (3) Enable interrupt on Capture/Compare */
	  /* (4) TS the filtering input off channel 1, and put into reset mode*/
	  /* (5) Enable counter */
	  TIM1->CCMR1 |= TIM_CCMR1_CC2S_1 | TIM_CCMR1_CC1S_0 | TIM_CCMR1_IC1F_0 | TIM_CCMR1_IC1F_1; /* (1)*/
	  TIM1->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC2P; /* (2) */
	  TIM1->DIER |= TIM_DIER_CC1IE; /* (3) */
	  TIM1->SMCR |= TIM_SMCR_TS_2 | TIM_SMCR_TS_0 | TIM_SMCR_SMS_2;
	  TIM1->CR1 |= TIM_CR1_CEN; /* (5) */

	  return;
}

void timer2_it_config()
{
	//Enable the interrupt this is needed to flicker an LED A#
	NVIC_InitTypeDef NVIC_InitStructure;
	//Enable Tim2 global interrupt
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Time base configuration */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period = 500 - 1; // 1kHz down to 2Hz (100 ms)
	TIM_TimeBaseStructure.TIM_Prescaler = 48000 - 1; // 48 MHz Clock down to 1 kHz (adjust per your clock)
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);
}

void
timer_sleep (timer_ticks_t ticks)
{
  timer_delayCount = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (timer_delayCount != 0u)
    ;
}

void
timer_tick (void)
{
  // Decrement to zero the counter used by the delay routine.
  if (timer_delayCount != 0u)
    {
      --timer_delayCount;
    }
}

// ----- SysTick_Handler() ----------------------------------------------------

void
SysTick_Handler (void)
{
#if defined(USE_HAL_DRIVER)
  HAL_IncTick();
#endif
  timer_tick ();
}

// ----------------------------------------------------------------------------
