####
TARGET = msp430f5529
BOARD = EXP430F5529
CC = msp430-gcc
VPATH = /home/macrobull/lib/msp430/src
export CPATH = /home/macrobull/lib/msp430/include
CFLAGS = -mmcu=$(TARGET) -D "_DEV_$(BOARD)" -g
OBJ = uart_demo.o uart.o interrupt_proxy.o qput.o

main: clean clear out.elf

debug: main
	msp430-objdump -D out.elf > asm.asm


flash: out.elf
	echo "opt fet_block_size 1024" > ~/.mspdebug
	-mspdebug tilib -d /dev/ttyACM0 "prog out.elf"


out.elf: $(OBJ)
	$(CC) -o out.elf $(CFLAGS) $(OBJ)

%.o : %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<

clear:
	clear

clean:
	-rm -r out.elf
	-find -name "*.o" -print -exec rm {} \;
	#-rm $(VPATH)/*.o
