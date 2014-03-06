####
TARGET = msp430f5529
BOARD = EXP430F5529
CC = msp430-gcc
VPATH = ~/lib/msp430/include
CFLAGS = -mmcu=$(TARGET) -I$(VPATH) -D "_DEV_$(BOARD)" -D _DISABLE_FLOAT -g
OBJ = uart_demo.o uart.o interrupt_proxy.o qput.o
# OBJ = lib-i2c_test1.o i2c.o uart.o qput.o  interrupt_proxy.o

main: clean clear out.elf

debug: main
	msp430-objdump -D out.elf > asm.asm


flash: out.elf
	mspdebug rf2500 "prog out.elf"


out.elf: $(OBJ)
	$(CC) -o out.elf $(CFLAGS) $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clear:
	clear

clean:
	-rm out.elf *.o
	#-rm $(VPATH)/*.o
