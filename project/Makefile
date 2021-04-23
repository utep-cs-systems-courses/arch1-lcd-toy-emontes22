# makfile configuration
COMMON_OBJECTS  =

CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h
LDFLAGS		= -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: runMain.elf

#additional rules for files

runMain.elf: ${COMMON_OBJECTS} wakeMain.o wdt_handler.o stateMachines.o buzzer.o led.o p2switches.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: runMain.elf
	msp430loader.sh runMain.elf

clean:
	rm -f *.o *.elf *~ *.~
