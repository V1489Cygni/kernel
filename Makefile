CFLAGS  := -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I.
LDFLAGS := -nostdlib -Wl,-N -Wl,-Ttext -Wl,100000

all:	kernel.bin

kernel.bin:	start.o	main.o scrn.o
	ld -T link.ld -o kernel.bin start.o main.o scrn.o
	@echo Done!

kernel2.bin: start.asm main.c scrn.c start.o
	gcc -o kernel.bin $(CFLAGS) start.o main.c scrn.c $(LDFLAGS)


start.o: start.asm
	nasm  -f elf -o start.o start.asm

main.o: main.c system.h
	gcc $(CFLAGS) -c -o main.o main.c

scrn.o: scrn.c system.h
	gcc  $(CFLAGS) -c -o scrn.o scrn.c

clean: 
	rm -f *.o *.bin
