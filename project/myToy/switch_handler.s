	.arch msp430g2553
	.text
	

	.global switch_interrupt_handler
	.extern P2IN,P2IES,P2IFG,SWITCHES,SW1,SW2,SW3,SW4,sw_high

	switch_interrupt_handler:
	    ; Load P2IFG and mask with SWITCHES
	    mov.b &P2IFG, r15
	    and.b &SWITCHES, r15

	    ; Load P2IN
	    mov.b P2IN, r14

	    ; Update interrupt sense based on button state
	    bit.b &SW1, r14
			bit.b &SW2, r14
			bit.b &SW3, r14
			bit.b &SW4, r14
	    jnz switch_interrupt_handler_skip_update
	    bic.b &SWITCHES, &P2IES
	    bis.b r15, &P2IES
	switch_interrupt_handler_skip_update:

	    ; Check which button was pressed and update sw_high
	    bit.b &SW1, r15
	    jnz switch_interrupt_handler_sw1
	    bit.b &SW2, r15
	    jnz switch_interrupt_handler_sw2
	    bit.b &SW3, r15
	    jnz switch_interrupt_handler_sw3
	    bit.b &SW4, r15
	    jnz switch_interrupt_handler_sw4
	    mov.b #0, &sw_high ; No button pressed
	    reti
	switch_interrupt_handler_sw1:
	    mov.b #1, &sw_high
	    reti
	switch_interrupt_handler_sw2:
	    mov.b #2, &sw_high
	    reti
	switch_interrupt_handler_sw3:
	    mov.b #3, &sw_high
	    reti
	switch_interrupt_handler_sw4:
	    mov.b #4, &sw_high
	    reti
