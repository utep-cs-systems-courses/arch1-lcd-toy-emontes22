#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

static char state = 0;

/* Function to blink the red led continuously */
void blinkRed()
{ 
  switch(state)
    {
    case 0: red_on = 1; green_on = 0; state++; break;
    case 1: red_on = 0; green_on = 0; state++; break;
    case 2: red_on = 1; green_on = 0; state++; break;
    case 3: red_on = 0; green_on = 0; state = 0; break;
    }
  led_changed = 1;
  led_update();
}

/* Function to blink the green led continuously */
void blinkGreen()
{
  switch(state)
    {
    case 0: red_on = 0; green_on = 1; state++; break;
    case 1: red_on = 0; green_on = 0; state++; break;
    case 2: red_on = 0; green_on = 1; state++; break;
    case 3: red_on = 0; green_on = 0; state = 0; break;
    }
   led_changed = 1;
  led_update();
}

/* Function to blink both leds at the same time */
void blinkBoth()
{
  switch(state)
    {
    case 0: red_on = 1; green_on = 1; state++; break;
    case 1: red_on = 0; green_on = 0; state++; break;
    case 2: red_on = 1; green_on = 1; state++; break;
    case 3: red_on = 0; green_on = 0; state = 0; break;
    }
  led_changed = 1;
  led_update();
}

/* Function to turn everything off */
void ledsOff()
{
  red_on = 0;
  green_on = 0;
  led_changed = 1;
  led_update();
}

/* State of the buttons */
void state_advance()
{
  switch(bPressed)
    {
    case 1: blinkRed(); break;
    case 2: blinkGreen(); break;
    case 3: blinkBoth(); buzzer_play(); break;
    case 4: ledsOff(); buzzer_set_period(0); break;
    }
}
