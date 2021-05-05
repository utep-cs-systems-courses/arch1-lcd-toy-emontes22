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

runMain.elf: ${COMMON_OBJECTS} wakeMain.o stateMachines.o buzzer.o led.o p2switches.o ../lib/libTimer.a ../lcdLib/lcdutils.o ../lcdLib/lcddraw.o ../lcdLib/font-5x7.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: runMain.elf
	msp430loader.sh runMain.elf

clean:
	rm -f *.o *.elf *~ *.~
