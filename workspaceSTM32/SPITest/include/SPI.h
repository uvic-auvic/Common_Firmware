//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef SPI_H_
#define SPI_H_

#include "stm32f0xx.h"
#include "stm32f0xx_spi.h"

#define SPI2_DATA (0xDE)
#define SPI1_DATA (0xCA)
// ----------------------------------------------------------------------------
void Configure_GPIO_LED(void);
void Configure_GPIO_SPI1(void);
void Configure_SPI1(void);
void Configure_GPIO_SPI2(void);
void Configure_SPI2(void);
void Configure_GPIO_Button(void);
void Configure_EXTI(void);
// ----------------------------------------------------------------------------

#endif // SPI_H_
