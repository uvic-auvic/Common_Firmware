//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#include "UART_DMA.h"

// ----------------------------------------------------------------------------
/* Private variables ---------------------------------------------------------*/
const uint8_t stringtosend[] = "DMA\n";
uint8_t stringtoreceive[] = "  ";


/**
  * @brief  This function :
             - Enables GPIO clock
             - Configures the Green LED pin on GPIO PC9
             - Configures the Orange LED pin on GPIO PC8
	     - Configures the orange LED pin on GPIO PC7
  * @param  None
  * @retval None
  */
__INLINE void Configure_GPIO_LED(void)
{
  /* Enable the peripheral clock of GPIOC */
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;

  /* Select output mode (01) on PC8 and PC9 */
  GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9)) \
                 | (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
  /* Select output mode (01) on PC7 */
  GPIOC->MODER = (GPIOC->MODER & ~(GPIO_MODER_MODER7)) | (GPIO_MODER_MODER7_0);
}

/**
  * @brief  This function :
             - Enables GPIO clock
             - Configures the USART1 pins on GPIO PA9 PA10
  * @param  None
  * @retval None
  */
__INLINE void Configure_GPIO_USART1(void)
{
  /* Enable the peripheral clock of GPIOA */
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

  /* GPIO configuration for USART1 signals */
  /* (1) Select AF mode (10) on PA9 and PA10 */
  /* (2) AF1 for USART1 signals */
  GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10))\
                 | (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1); /* (1) */
  GPIOA->AFR[1] = (GPIOA->AFR[1] &~ (GPIO_AFRH_AFRH1 | GPIO_AFRH_AFRH2))\
                  | (1 << (1 * 4)) | (1 << (2 * 4)); /* (2) */
}

/**
  * @brief  This function configures DMA.
  * @param  None
  * @retval None
  */
__INLINE void Configure_DMA1(void)
{
  /* Enable the peripheral clock DMA1 */
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;

  /* DMA1 Channel2 USART1_TX config */
  /* (1)  Peripheral address */
  /* (2)  Memory address */
  /* (3)  Memory increment */
  /*      Memory to peripheral */
  /*      8-bit transfer */
  /*      Transfer complete IT */
  DMA1_Channel2->CPAR = (uint32_t)&(USART1->TDR); /* (1) */
  DMA1_Channel2->CMAR = (uint32_t)stringtosend; /* (2) */
  DMA1_Channel2->CCR |= DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE; /* (3) */

  /* DMA1 Channel2 USART_RX config */
  /* (4)  Peripheral address */
  /* (5)  Memory address */
  /* (6)  Data size */
  /* (7)  Memory increment */
  /*      Peripheral to memory*/
  /*      8-bit transfer */
  /*      Transfer complete IT */
  DMA1_Channel3->CPAR = (uint32_t)&(USART1->RDR); /* (4) */
  DMA1_Channel3->CMAR = (uint32_t)stringtoreceive; /* (5) */
  DMA1_Channel3->CNDTR = sizeof(stringtoreceive); /* (6) */
  DMA1_Channel3->CCR |= DMA_CCR_MINC | DMA_CCR_TCIE | DMA_CCR_EN; /* (7) */

  /* Configure IT */
  /* (8) Set priority for DMA1_Channel2_3_IRQn */
  /* (9) Enable DMA1_Channel2_3_IRQn */
  NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0); /* (8) */
  NVIC_EnableIRQ(DMA1_Channel2_3_IRQn); /* (9) */
}

/**
  * @brief  This function configures USART1.
  * @param  None
  * @retval None
  */
__INLINE void Configure_USART1(void)
{
  /* Enable the peripheral clock USART1 */
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

  /* Configure USART1 */
  /* (1) oversampling by 16, 9600 baud */
  /* (2) Enable DMA in reception and transmission */
  /* (3) 8 data bit, 1 start bit, 1 stop bit, no parity, reception and transmission enabled */
  USART1->BRR = 480000 / 96; /* (1) */
  USART1->CR3 = USART_CR3_DMAT | USART_CR3_DMAR; /* (2) */
  USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE; /* (3) */

  while((USART1->ISR & USART_ISR_TC) != USART_ISR_TC)/* polling idle frame Transmission */
  {
    /* add time out here for a robust application */
  }
  USART1->ICR |= USART_ICR_TCCF;/* Clear TC flag */
  USART1->CR1 |= USART_CR1_TCIE;/* Enable TC interrupt */
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

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles EXTI 0 1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_1_IRQHandler(void)
{
  EXTI->PR |= 1;

  /* start 8-bit transmission with DMA */
  DMA1_Channel2->CCR &=~ DMA_CCR_EN;
  DMA1_Channel2->CNDTR = sizeof(stringtosend);/* Data size */
  DMA1_Channel2->CCR |= DMA_CCR_EN;
}

/**
  * @brief  This function handles DMA1 channel 2 and 3 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel2_3_IRQHandler(void)
{

  if((DMA1->ISR & DMA_ISR_TCIF2) == DMA_ISR_TCIF2)
  {
    DMA1->IFCR |= DMA_IFCR_CTCIF2;/* Clear TC flag */

    GPIOC->ODR ^= GPIO_ODR_8; /* Toggle Orange LED */
  }
  else if((DMA1->ISR & DMA_ISR_TCIF3) == DMA_ISR_TCIF3)
  {
    DMA1->IFCR |= DMA_IFCR_CTCIF3;/* Clear TC flag */

    if(strcmp("OK",(const char *)stringtoreceive) == 0)
    {
      GPIOC->ODR ^= GPIO_ODR_9; /* Toggle Green LED */
    }

    DMA1_Channel3->CCR &=~ DMA_CCR_EN;
    DMA1_Channel3->CNDTR = sizeof(stringtoreceive);/* Data size */
    DMA1_Channel3->CCR |= DMA_CCR_EN;
  }
  else
  {
    NVIC_DisableIRQ(DMA1_Channel2_3_IRQn);/* Disable DMA1_Channel2_3_IRQn */
  }
}

// ----------------------------------------------------------------------------
