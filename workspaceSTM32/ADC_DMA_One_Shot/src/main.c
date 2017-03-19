//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "ADC_DMA_One_Shot..h"

extern volatile uint16_t error;
/*
 *
 ===============================================================================
                    ##### How to test this example #####
 ===============================================================================
    - This example configures the ADC to convert 4 channels (CH1, 9, 10 and 17)
    - The data are stored thanks to the DMA.
    - The code launches a continuous conversion.
    - The conversion is stopped if the USER push-button is pressed and start again
      in case of a new push. The orange led is switched on while ADC on hold.
    - The green led blinks at each DMA transfer (blinking not visible).
      In case of failure, the orange led blinks coding the error type
 *
 */

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int
main(int argc, char* argv[])
{
  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Hello ARM World!");

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %u Hz\n", SystemCoreClock);


  ConfigureGPIO();
  ConfigureExternalIT();
  SetClockForADC();
  CalibrateADC();
  ConfigureGPIOforADC();
  EnableADC();
  ConfigureADC();
  ConfigureDMA();
  ADC1->CR |= ADC_CR_ADSTART; /* start the ADC conversions */

  while (error < ERROR_UNEXPECTED_DMA_IT) /* loop till no unrecoverable error */
  {
    __WFI();
  }
  DisableADC();
  SysTick_Config(48000);/* 1ms config */

  // Infinite loop
  while (1)
    {

    }
  // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
