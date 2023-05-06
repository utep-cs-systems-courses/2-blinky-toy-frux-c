	.arch msp430g2553
	.text
	

	.global switch_interrupt_handler
	.extern P2IN,P2IES,P2IFG,SWITCHES,SW1,SW2,SW3,SW4,sw_high
	switch_interrupt_handler:
			;update switch interrupt sense to detect changes from current buttons
			;if switch is up, sense down
		;	bis.b &P2IES, &P2IN
		;	bis.b &P2IES, #0xf
			;if switch down, sense up
		;	bit.b &P2IES, &P2IN
		;	bic.b &P2IES, #0xf
			
			mov #1, &sw_high
			cmp.b &SW1, &P2IN
			jz switch_interrupt_handler_sw1
			cmp.b &SW2, &P2IN
			jz switch_interrupt_handler_sw2
			cmp.b &SW3, &P2IN
			jz switch_interrupt_handler_sw3
			cmp.b &SW4, &P2IN
			jz switch_interrupt_handler_sw4
			reti
			
	switch_interrupt_handler_sw1:
	    mov #1, &sw_high
	    reti
	switch_interrupt_handler_sw2:
	    mov #2, &sw_high
	    reti
	switch_interrupt_handler_sw3:
	    mov #3, &sw_high
	    reti
	switch_interrupt_handler_sw4:
	    mov #4, &sw_high
	    reti
