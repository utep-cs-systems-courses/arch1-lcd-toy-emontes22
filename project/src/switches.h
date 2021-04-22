#ifndef switches_included
#define switches_included
/* P2.0 to P2.3 are from green board */
#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1 | SW2 | SW3 | SW4) /* 4 switches on this board */

void switch_init();
void switch_interrupt_handler();

extern char switch_state_down, switch_state_changed, bPressed; /* effectively boolean */

#endif // included
