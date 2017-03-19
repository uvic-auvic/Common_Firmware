//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "PWM_Edge_Aligned.h"


/*
 *
 ===============================================================================
                    ##### How to test this example #####
 ===============================================================================
    - This example configures the TIM1 in order to generate a PWM edge aligned
      on OC1 (channel 1)with a period of 9 microseconds and a 4/9 duty cycle.
      The GPIO PA8, corresponding to TIM1_CH1, is configured as alternate function
      and the AFR2 is selected.
    - To test this example, the user must monitor the signal on PA8.
    - This example can be easily ported on any other timer by modifying TIMx
      definition. The corresponding GPIO must be also adapted according to
      the datasheet.
    - The green LED is switched on.

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
   ConfigureTIMxAsPWM_EdgeAligned();
   GPIOC->BSRR = 1<<9; /* switch on green led */
  // Infinite loop
  while (1)
    {
	    __WFI();
    }
  // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
