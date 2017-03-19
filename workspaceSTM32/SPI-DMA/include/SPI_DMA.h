//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef SPI_DMA_H_
#define SPI_DMA_H_

#include "stm32f0xx.h"
#include "stm32f0xx_spi.h"
#include "string.h" /* for strcmp */
#include "stdlib.h" /* for malloc */

/*
 * PRIVATE FUNCTION PROTOTYPES
 */
void Configure_GPIO_LED(void);
void Configure_GPIO_SPI1(void);
void Configure_DMA1_SPI1(void);
void Configure_SPI1(void);
void Configure_GPIO_SPI2(void);
void Configure_DMA1_SPI2(void);
void Configure_SPI2(void);
void Configure_GPIO_Button(void);
void Configure_EXTI(void);

#endif // SPI_DMA_H_
