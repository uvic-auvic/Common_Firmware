//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef I2C_H_
#define I2C_H_

#include "stm32f0xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C1_OWN_ADDRESS (0x5A)
#define I2C_BYTE_TO_SEND (0xA5)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Configure_GPIO_LED(void);
void Configure_GPIO_I2C1(void);
void Configure_I2C1_Slave(void);
void Configure_GPIO_I2C2(void);
void Configure_I2C2_Master(void);
void Configure_GPIO_Button(void);
void Configure_EXTI(void);


// ----------------------------------------------------------------------------

#endif // I2C_H_
