//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "ADC_example.h"

/*
 *
 ===============================================================================
                    ##### How to test this example #####
 ===============================================================================
    - This example configures the ADC to convert 4 channels (CH1, 9, 10 and 17)
    - The  end of conversion (EOC) and end of sequence (EOSEQ) are managed by interrupt.
    - At each TIM15 trigger occurence, a conversion sequence is launched, i.e the 4 channels
      are successively converted.
    - The conversion is stopped if the USER push-button is pressed and start again
      in case of a new push and synchronized by TIM15 with the scanning direction toggled.
      As the data table is always filled in the same way, the scan direction change
      can be checked by monitoring in live the memory at ADC_array[] addresses.
    - The green led is toggled at each end of ADC sequence (blinking is not visible).
      While conversion is stopped  by pushing USER button,
      the orange led and the green led are switched on.
      To start again the AD Conversion, push again the user button. The two leds
      are switched off and the first green led toggling is visible as the conversion
      will wait for a TIM15 external trigger.
    - In case of failure, the ADC is disabled
      and the orange led blinks coding the error type
 *
 */



// ----- main() ---------------------------------------------------------------
/* Private variables ---------------------------------------------------------*/
extern uint16_t error;  //initialized at 0 and modified by the functions
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

  /* defines the upper limit 15% above the factory value
     the value is adapted according to the application power supply
     versus the factory calibration power supply */
  uint16_t vrefint_high = (*VREFINT_CAL_ADDR)* VDD_CALIB / VDD_APPLI * 115 / 100;
  /* defines the lower limit 15% below the factory value
     the value is adapted according to the application power supply
     versus the factory calibration power supply */
  uint16_t vrefint_low = (*VREFINT_CAL_ADDR) * VDD_CALIB / VDD_APPLI * 85 / 100;

    ConfigureGPIO();
    SetClockForADC();
    CalibrateADC();
    EnableADC();
    ConfigureADC();
    ConfigureTIM15();
    ADC1->CR |= ADC_CR_ADSTART; /* start the ADC conversion */

    while (error == 0) /* Loop till the measure is in the range */
    {
      while ((ADC1->ISR & ADC_ISR_EOC) == 0); /* wait end of conversion */

      if ((ADC1->DR > vrefint_high) && (ADC1->DR > vrefint_low))
      {
        error |= WARNING_MEASURE; /* report a warning, the measure being out of range due to VDD shift */
      }
      GPIOC->ODR ^= (1<<9); /* Toggle green led on PC9 */
    }
    DisableADC();
    SysTick_Config(48000); /* 1ms config */

  // Infinite loop, never return.
}


#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
