NAME = main

$(NAME).ihx:
	sdcc main.c

clean:
	rm -f *.asm *.rel *.lst *.sym *.ihx *.lk *.map *.mem *.rst
