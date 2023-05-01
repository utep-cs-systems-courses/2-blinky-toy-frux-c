#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "main.h"

volatile short wdt_count = 0, sw_high = 0;

volatile short marry_lamb_freq_count = 0, twinkle_freq_count = 0, jingle_freq_count = 0, happy_birthday_freq_count = 0;

short marry_lamb_freq [] = {
    659, 587, 523, 587, 659, 659, 659,
    587, 587, 587, 659, 784, 784,
    659, 587, 523, 587, 659, 659, 659,
    659, 587, 587, 659, 587, 523
};

short twinkle_freq [] = {
  659, 659, 880, 880, 987, 987, 880,
  784, 784, 659, 880, 880, 784, 784,
  659, 659, 880, 880, 987, 987, 880,
  784, 784, 659, 880, 880, 784, 784,
  659, 659, 880, 880, 987, 987, 880,
  784, 784, 659, 880, 880, 784, 784,
  659, 659, 880, 880, 987, 987, 880,
  784, 784, 659, 880, 880, 784, 784,
};

short jingle_freq [] = {
  659, 659, 659, 0, 659, 659, 659, 0,
  659, 659, 659, 0, 659, 659, 659, 0,
  659, 698, 523, 659, 784, 784,
  659, 659, 659, 0, 659, 659, 659, 0,
  659, 659, 659, 0, 659, 659, 659, 0,
  659, 698, 523, 659, 784, 784,
  659, 659, 784, 784, 880, 880,
  784, 784, 698, 698, 659, 659, 587,
  659, 784, 784, 659, 659, 587, 659,
  784, 784, 880, 880, 987, 987, 880,
  784, 784, 698, 698, 659, 659, 587,
  659, 784, 784, 659, 659, 587, 0
};

short happy_birthday_freq [] = {
  659, 659, 698, 659, 784, 0, 659, 659,
  698, 659, 880, 0, 784, 0, 659, 659,
  1175, 932, 1175, 0, 1047, 0, 880, 0,
  698, 784, 659, 0, 784, 880, 784, 0
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
	switch(sw_high){
		case 1:
			marry_lamb_freq_count = MARRY_LAMB_LENGTH>marry_lamb_freq_count?marry_lamb_freq_count:0;
			buzzer_set_period(marry_lamb_freq[marry_lamb_freq_count++]);
			break;
		case 2:
			twinkle_freq_count = TWINKLE_LENGTH>twinkle_freq_count?twinkle_freq_count:0;
			buzzer_set_period(twinkle_freq[twinkle_freq_count++]);
			break;
		case 3:
			jingle_freq_count = JINGLE_LENGTH>jingle_freq_count?jingle_freq_count:0;
			buzzer_set_period(jingle_freq[jingle_freq_count++]);
			break;
		case 4:
			happy_birthday_freq_count = HAPPY_BIRTHDAY_LENGTH>happy_birthday_freq_count?happy_birthday_freq_count:0;
			buzzer_set_period(happy_birthday_freq[happy_birthday_freq_count++]);
			break;
		default:
			buzzer_set_period(0);
	}
}
// void
// switch_interrupt_handler()
// {
//   unsigned char p2val = P2IFG & SWITCHES;		
// 	unsigned char p2val2 = P2IN;
// 	/* update switch interrupt sense to detect changes from current buttons */
// 	P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
// 	P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
	
// 	if((~p2val2 & SW1) && (~p2val2 & SW4)){ sw_high = 0; return; }
	
// 	if(p2val & SW1){ sw_high = 1;}
// 	if(p2val & SW2){ sw_high = 2;}
// 	if(p2val & SW3){ sw_high = 3;}
// 	if(p2val & SW4){ sw_high = 4;}

// }}

/* Switch on P2 (SW1|SW2|SW3|SW4) */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
		switch_interrupt_handler();	/* single handler for all switches */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
  }
}
void
__interrupt_vec(WDT_VECTOR) WDT(){
	/** wdt */
	if(wdt_count == 50){
		wdt_count = 0;
		play_song();
	}else{
		wdt_count++;
	}
}

