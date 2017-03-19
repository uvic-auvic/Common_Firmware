//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "Timer.h"
#include "UART_DMA.h"

/*
 *
 ===============================================================================
                    ##### How to test this example #####
 ===============================================================================
   - Plug cable " USB to TTL 3V3 " (from FTDIChip)
   - Connect FTDI Rx to USART1 Tx(PA9)and FTDI Tx to USART1 Rx(PA10) and both GNDs
   - Launch serial communication SW
   - Launch the program
   - Press the user button
   - The orange LED should toggle if transmission goes well
     (DMA mode)
   - Send "OK" with PC (3 characters: 'O','K',0x00)
   - The green LED should toggle if reception goes well
     (DMA mode)

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
  
  Configure_GPIO_LED();
  Configure_GPIO_USART1();
  Configure_DMA1();
  Configure_USART1();
  Configure_GPIO_Button();
  Configure_EXTI();

  // Infinite loop
  while (1)
    {

    }
  // Infinite loop, never return.
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------