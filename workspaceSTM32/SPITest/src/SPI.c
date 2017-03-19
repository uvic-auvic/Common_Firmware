//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "SPI.h"


// ----------------------------------------------------------------------------
__INLINE void Configure_GPIO_LED(void)
{
  /* Enable the peripheral clock of GPIOC */
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

  /* Select output mode (01) on PC6, PC7, PC8 and PC9 */
  GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER6 | GPIO_MODER_MODER7)) \
                 | (GPIO_MODER_MODER6_0 | GPIO_MODER_MODER7_0);
  GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9)) \
                 | (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
}

/**
  * @brief  This function :
             - Enables GPIO clock
             - Configures the SPI1 pins on GPIO PA4 PA5 PA6 PA7
  * @param  None
  * @retval None
  */
__INLINE void Configure_GPIO_SPI1(void)
{
  /* Enable the peripheral clock of GPIOA */
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

  /* (1) Select AF mode (10) on PA4, PA5, PA6, PA7 */
  /* (2) AF0 for SPI1 signals */
  GPIOA->MODER = (GPIOA->MODER
                  & ~(GPIO_MODER_MODER4 | GPIO_MODER_MODER5 | \
                      GPIO_MODER_MODER6 | GPIO_MODER_MODER7))\
                  | (GPIO_MODER_MODER4_1 | GPIO_MODER_MODER5_1 |\
                     GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1); /* (1) */
  GPIOA->AFR[0] = (GPIOA->AFR[0] & \
                   ~(GPIO_AFRL_AFRL4 | GPIO_AFRL_AFRL5 |\
                     GPIO_AFRL_AFRL6 | GPIO_AFRL_AFRL7)); /* (2) */
}

/**
  * @brief  This function configures SPI1.
  * @param  None
  * @retval None
  */
__INLINE void Configure_SPI1(void)
{
  /* Enable the peripheral clock SPI1 */
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

  /* Configure SPI1 in master */
  /* (1) Master selection, BR: Fpclk/256 (due to C27 on the board, SPI_CLK is set to the minimum)
         CPOL and CPHA at zero (rising first edge) */
  /* (2) Slave select output enabled, RXNE IT, 8-bit Rx fifo */
  /* (3) Enable SPI1 */
  SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR; /* (1) */
  SPI1->CR2 = SPI_CR2_SSOE | SPI_CR2_RXNEIE | SPI_CR2_FRXTH | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0; /* (2) */
  SPI1->CR1 |= SPI_CR1_SPE; /* (3) */

  /* Configure IT */
  /* (4) Set priority for SPI1_IRQn */
  /* (5) Enable SPI1_IRQn */
  NVIC_SetPriority(SPI1_IRQn, 0); /* (4) */
  NVIC_EnableIRQ(SPI1_IRQn); /* (5) */
}

/**
  * @brief  This function :
             - Enables GPIO clock
             - Configures the SPI2 pins on GPIO PB12 PB13 PB14 PB15
  * @param  None
  * @retval None
  */
__INLINE void Configure_GPIO_SPI2(void)
{
  /* Enable the peripheral clock of GPIOB */
  RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

  /* (1) Select AF mode (10) on PB12, PB13, PB14, PB15 */
  /* (2) AF0 for SPI2 signals */
  GPIOB->MODER = (GPIOB->MODER
                 & ~(GPIO_MODER_MODER12 | GPIO_MODER_MODER13 | \
                     GPIO_MODER_MODER14 | GPIO_MODER_MODER15))\
                 | (GPIO_MODER_MODER12_1 | GPIO_MODER_MODER13_1|\
                    GPIO_MODER_MODER14_1 | GPIO_MODER_MODER15_1); /* (1) */
  GPIOB->AFR[1] = (GPIOB->AFR[1] & \
                   ~(GPIO_AFRH_AFRH4 | GPIO_AFRH_AFRH5 |\
                     GPIO_AFRH_AFRH6 | GPIO_AFRH_AFRH7)); /* (2) */
}

/**
  * @brief  This function configures SPI2.
  * @param  None
  * @retval None
  */
__INLINE void Configure_SPI2(void)
{
   /* Enable the peripheral clock SPI2 */
  RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;

  /* Configure SPI2 in slave */
  /* nSS hard, slave, CPOL and CPHA at zero (rising first edge) */
  /* (1) RXNE IT, 8-bit Rx fifo */
  /* (2) Enable SPI2 */
  SPI2->CR2 = SPI_CR2_RXNEIE | SPI_CR2_FRXTH | SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0; /* (1) */
  SPI2->CR1 |= SPI_CR1_SPE; /* (2) */

  /* Configure IT */
  /* (3) Set priority for SPI2_IRQn */
  /* (4) Enable SPI2_IRQn */
  NVIC_SetPriority(SPI2_IRQn, 0); /* (3) */
  NVIC_EnableIRQ(SPI2_IRQn); /* (4) */
}

/**
  * @brief  This function :
             - Enables GPIO clock
             - Configures the Push Button GPIO PA0
  * @param  None
  * @retval None
  */
__INLINE void Configure_GPIO_Button(void)
{
  /* Enable the peripheral clock of GPIOA */
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

  /* Select mode */
  /* Select input mode (00) on PA0 */
  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER0));
}

/**
  * @brief  This function configures EXTI.
  * @param  None
  * @retval None
  */
__INLINE void Configure_EXTI(void)
{
  /* Configure Syscfg, exti and nvic for pushbutton PA0 */
  /* (1) PA0 as source input */
  /* (2) unmask port 0 */
  /* (3) Rising edge */
  /* (4) Set priority */
  /* (5) Enable EXTI0_1_IRQn */
  SYSCFG->EXTICR[0] = (SYSCFG->EXTICR[0] & ~SYSCFG_EXTICR1_EXTI0) | SYSCFG_EXTICR1_EXTI0_PA; /* (1) */
  EXTI->IMR |= EXTI_IMR_MR0; /* (2) */
  EXTI->RTSR |= EXTI_RTSR_TR0; /* (3) */
  NVIC_SetPriority(EXTI0_1_IRQn, 0); /* (4) */
  NVIC_EnableIRQ(EXTI0_1_IRQn); /* (5) */
}



// ----------------------------------------------------------------------------
