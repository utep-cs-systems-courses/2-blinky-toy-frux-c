#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)


/** switches are defined on port 2 */

#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1|SW2|SW3|SW4) 	/** switches p2.(0-3) */
#define NOTE_LENGTH 26
int wdt_count = 0, sw1_toggle = 0, sw2_toggle = 0, sw3_toggle = 0, sw4_toggle = 0;
int note_count = 0;
int marry_lamb_freq [] = {
    659, 587, 523, 587, 659, 659, 659,
    587, 587, 587, 659, 784, 784,
    659, 587, 523, 587, 659, 659, 659,
    659, 587, 587, 659, 587, 523
};

void main(void) 
{  

	P1DIR |= LEDS;
	P1OUT &= ~LEDS;		/* leds initially off */

	P2REN |= SWITCHES;		/* enables resistors for switches */
	P2IE |= SWITCHES;		/* enable interrupts from switches */
	P2OUT |= SWITCHES;		/* pull-ups for switches */
	P2DIR &= ~SWITCHES;		/* set switches' bits for input */

	configureClocks(); /** setup master oscillator, CPU & peripheral clocks */
	enableWDTInterrupts(); /* enable periodic interrupt **/	
	buzzer_init();

  or_sr(0x18);  // CPU off, GIE on
} 

void
play_song(){
	if(sw3_toggle){
		buzzer_set_period(marry_lamb_freq[note_count]);
	}
	else{
		buzzer_set_period(0);
	}
}
void
switch_interrupt_handler()
{
  char p2val = P2IN;		/* switch is in P1 */

	/* update switch interrupt sense to detect changes from current buttons */
	P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
	P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */

	/* up=red, down=green */
	if (p2val & SW1) {
		sw1_toggle = sw1_toggle==0?1:0;
	}
	if(p2val & SW2) {
		sw2_toggle = sw2_toggle==0?1:0;
	}
	if(p2val & SW3){
		sw3_toggle = sw3_toggle==0?1:0;
	}
	if(p2val & SW4){
		sw4_toggle = sw4_toggle==0?1:0;
	}
}


/* Switch on P2 (SW1|SW2|SW3|SW4) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
void
__interrupt_vec(WDT_VECTOR) WDT(){
	if(wdt_count == 125){
		wdt_count = 0;
		note_count++;
		if(note_count >= NOTE_LENGTH){
			note_count = 0;
		}
	}else{
		wdt_count++;
	}
	/** wdt */
	if(sw1_toggle){
		P1OUT |= LED_GREEN;
	}else{
		P1OUT &= ~LED_GREEN;
	}
	if(sw2_toggle){
		P1OUT |= LED_RED;
	}else{
		P1OUT &= ~LED_RED;
	}
	play_song();
}

