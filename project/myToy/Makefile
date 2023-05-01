# makfile configuration
COMMON_OBJECTS  = main.o buzzer.o switch_handler.o main.h
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: main.elf

#additional rules for files
main.elf: ${COMMON_OBJECTS} ~/lib/libTimer.a ~/timerLib/libTimer.h
	${CC} ${CFLAGS} -o $@ $^

load: main.elf
	msp430loader.sh  $^

clean: $^
	rm -f *.o *.elf

main.o: main.c main.h
buzzer.o: buzzer.h
switch_handler.o: switch_handler.s main.h

