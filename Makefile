CC=gcc
AS=yasm
LD=ld

CFLAGS=-m32 -fno-stack-protector -fno-builtin -nostdinc -g -O -Wall -I. -std=c99
ASFLAGS=-f elf32
LDFLAGS=-melf_i386 -T link.ld

CSOURCES=./irq/irq.c ./gdt/gdt.c ./idt/idt.c ./isr/isr.c ./pit/pit.c ./service/service.c\
./output/output.c ./input/input.c ./shell/shell.c ./kernel/kernel.c ./rtc/rtc.c
ASMSOURCES=./loader/loader.asm ./gdt/gdt.asm ./idt/idt.asm ./isr/isr.asm ./irq/irq.asm

COBJECTS=$(CSOURCES:.c=.o)
ASMOBJECTS=$(ASMSOURCES:.asm=_asm.o)

OUTPUT=kernel.bin

all: $(ASMOBJECTS) $(COBJECTS)
	$(LD) $(LDFLAGS) -o $(OUTPUT) $(ASMOBJECTS) $(COBJECTS)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%_asm.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OUTPUT) $(COBJECTS) $(ASMOBJECTS)

