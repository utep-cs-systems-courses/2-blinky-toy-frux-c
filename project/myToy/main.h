#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

#define LED_RED BIT0               // P1.0
#define LED_GREEN BIT6             // P1.6
#define LEDS (BIT0 | BIT6)


/** switches are defined on port 2 */

const char SW1 = BIT0;
const char SW2 = BIT1;
const char SW3 = BIT2;
const char SW4 = BIT3;
const char SWITCHES = (SW1|SW2|SW3|SW4);	/** switches p2.(0-3) */

/** define song length */
const short MARRY_LAMB_LENGTH = 26;
const short TWINKLE_LENGTH = 56;
const short JINGLE_LENGTH = 85;
const short HAPPY_BIRTHDAY_LENGTH = 32;

void play_song();
void switch_interrupt_handler();
