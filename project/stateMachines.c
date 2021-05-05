#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "p2switches.h"
#include "lcdutils.h"
#include "lcddraw.h"

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

void drawFigure()
{
  u_char offset_r = 100, offset_c = 65;
  for (int r = 0; r <= 50; r++)
    {
      for (int c = 0; c <= r; c++)
	{
	  drawPixel(offset_c - c, offset_r - r, COLOR_BLUE);
	  drawPixel(offset_c + c, offset_r - r, COLOR_BLUE);
	  drawPixel(offset_c + c, offset_r + r, COLOR_BLUE);
	  drawPixel(offset_c - c, offset_r + r, COLOR_BLUE);
	}
    }
}
