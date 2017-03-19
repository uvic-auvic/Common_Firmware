//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "I2C.h"
/*
 *
 ===============================================================================
                    ##### How to test this example #####
 ===============================================================================
    - Plug wires between PB6/PB10 and PB7/PB11, 4K7 PU are already on the board
    - Launch the program
    - Press the user button to initiate a read request by master
      then slave sends a byte
    - The green LED toggles if everything goes well
    - The orange LED lit in other cases
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

  timer_start();

  Configure_GPIO_LED();
	GPIOC->BSRR = GPIO_BSRR_BS_8; /* lit blue LED */
  Configure_GPIO_I2C1();
  Configure_I2C1_Slave();
  Configure_GPIO_I2C2();
  Configure_I2C2_Master();
  Configure_GPIO_Button();
  Configure_EXTI();

  uint32_t seconds = 0;

  // Infinite loop
  while (1)
    {


      ++seconds;

      // Count seconds on the trace device.
      trace_printf("Second %u\n", seconds);
    }
  // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------