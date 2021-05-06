#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include <abCircle.h>
#include "buzzer.h"
#include "led.h"
#include "stateMachines.h"

#define GREEN_LED BIT6

static char button = 0;
short redrawScreen = 1; /* Checks whether screen needs to be redrawn */

void wdt_c_handler()
{
  u_int read = p2sw_read(); //To read a button pressed
  static int secCount = 0;
  secCount++;

  /*Checking every time if a button is pressed*/
  if((read & 1) == 0)
    button = 1;
  if((read & 2) == 0)
    button = 2;
  if((read & 4) == 0)
    button = 3;
  if((read & 8) == 0)
    button = 4;
  
  /*When a button is pressed it will go to main to execute command*/
  switch(button)
    {
    case 1:
      redrawScreen = 1;
      break;
    case 2:
      redrawScreen = 1;
      break;
    case 3:
      if(secCount == 250)
	redrawScreen = 1;
      break;
    case 4:
      if(secCount == 250)
	redrawScreen = 1;
      break;
    }
  
  if(secCount == 250)
    secCount = 0;
}

void main()
{
  P1DIR |= GREEN_LED; /* Green led on when CPU on */
  P1OUT |= GREEN_LED;

  configureClocks();
  lcd_init();
  led_init();
  buzzer_init();
  p2sw_init(15);
  enableWDTInterrupts(); //enable periodic interrupt
  or_sr(0x8); //GIE (enable interrupts)
  
  while(1) /* Run forever */
    {
      if(redrawScreen)
	{
	  redrawScreen = 0;
	  
	  switch(button)
	    {
	    case 1: /*S1 is pressed and red led is on and screen is color white*/
	      clearScreen(COLOR_BLACK);
	      drawFigure();
	      blinkRed();
	      buzzer_set_period(0);
	      break;
	    case 2: /*S2 is pressed and screen is black, green led on and draws a blue square*/
	      clearScreen(COLOR_WHITE);
	      animation();
	      ledsOff();
	      buzzer_play();
	      break;
	    case 3: /*S3 is pressed and screen is blue, makes sound and prints "hello" to screen*/
	      clearScreen(COLOR_BLUE);
	      blinkBoth();
	      buzzer_set_period(0);
	      drawString8x12(10, 60, "Hello", COLOR_WHITE, COLOR_BLUE);
	      break;
	    case 4: /* everything is off, screen is white and prints "Bye" to screen*/
	      clearScreen(COLOR_WHITE);
	      blinkGreen();
	      buzzer_set_period(0);
	      drawString11x16(20, 80, "Bye", COLOR_BLACK, COLOR_WHITE);
	      break;
	    }
	}
      
      P1OUT &= ~LED_GREEN;/* green off */
      or_sr(0x10); /* CPU OFF */
      P1OUT |= LED_GREEN; /* green on */
    }
}
