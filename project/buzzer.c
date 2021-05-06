#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

static char buzzerState = 0;

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void buzzer_set_period(short cycles) /* buzzer clock = 2MHz.  (period of 1k results in 2kHz tone) */
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

/* Function to play some notes */
void buzzer_play(){

  switch(buzzerState)
    {
    case 0: buzzer_set_period(750); buzzerState++; break;
    case 1:
    case 2:
    case 3: buzzer_set_period(630); buzzerState++; break;
    case 4:
    case 5:
    case 6: buzzer_set_period(560); buzzerState++; break;
    case 7:
    case 8:
    case 9: buzzer_set_period(950); buzzerState++; break;
    case 10:
    case 11:
    case 12: buzzer_set_period(500); buzzerState = 0; break;
  }
}

