//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef ADC_DMA_One_Shot._H_
#define ADC_DMA_One_Shot._H_

#include "stm32f0xx.h"

#define ERROR_DMA_XFER 0x01
#define ERROR_UNEXPECTED_DMA_IT 0x02
#define ERROR_UNEXPECTED_ADC_IT 0x04
#define ERROR_UNEXPECTED_EXT_IT 0x08

#define NUMBER_OF_ADC_CHANNEL 4

/* Internal voltage reference calibration value address */
#define VREFINT_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7BA))
/* Private function prototypes -----------------------------------------------*/
void ConfigureGPIO(void);
void ConfigureExternalIT(void);
void SetClockForADC(void);
void CalibrateADC(void);
void ConfigureADC(void);
void ConfigureGPIOforADC(void);
void ConfigureDMA(void);
void EnableADC(void);
void DisableADC(void);

// ----------------------------------------------------------------------------

#endif // ADC_DMA_One_Shot._H_
