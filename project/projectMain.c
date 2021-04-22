#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "libTimer.h"

int main(void)
{
  configureClocks();                /* setup master oscillator, CPU & peripheral clocks */
  led_init();
  enableWDTInterrupts();            /* enable periodic interrupt */
  switch_init();
  buzzer_init();
  or_sr(0x18);                      // CPU off, GIE on
}
