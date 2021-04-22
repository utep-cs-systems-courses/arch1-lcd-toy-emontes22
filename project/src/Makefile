# makfile configuration
COMMON_OBJECTS  =

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: projectMain.elf

#additional rules for files

projectMain.elf: ${COMMON_OBJECTS} projectMain.c stateMachines.o buzzer.o switches.o led.o p2_interrupt_handler.o wdInterruptHandler.o ../lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: projectMain.elf
	msp430loader.sh projectMain.elf

clean:
	rm -f *.o *.elf *~ *.~

stateMachines.o: stateMachines.c stateMachines.h
led.o: led.c led.h
switches.o: switches.c switches.h
buzzer.o: buzzer.c buzzer.h
wdInterruptHandler.o: wdInterruptHandler.c
p2_interrupt_handler.o: p2_interrupt_handler.c
