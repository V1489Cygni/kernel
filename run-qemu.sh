nasm -f elf -o loader.o ./loader/loader.asm
nasm -f elf -o gdt_asm.o ./gdt/gdt.asm
nasm -f elf -o idt_asm.o ./idt/idt.asm
nasm -f elf -o isr_asm.o ./isr/isr.asm
nasm -f elf -o irq_asm.o ./irq/irq.asm
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o irq.o ./irq/irq.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o gdt.o ./gdt/gdt.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o idt.o ./idt/idt.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o isr.o ./isr/isr.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o pit.o ./pit/pit.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o service.o ./service/service.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o output.o ./output/output.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o input.o ./input/input.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o shell.o ./shell/shell.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o kernel.o ./kernel/kernel.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o rtc.o ./rtc/rtc.c
ld -T link.ld -o kernel.bin gdt_asm.o gdt.o idt_asm.o idt.o isr_asm.o isr.o loader.o pit.o service.o irq_asm.o irq.o output.o input.o shell.o rtc.o kernel.o
rm *.o
echo "drive c: file=\"`pwd`/core.img\" partition=1" > ~/.mtoolsrc
dd if=/dev/zero of=core.img count=088704 bs=512
mpartition -I c:
mpartition -c -t 88 -h 16 -s 63 c:
mformat c:
mmd c:/boot
mmd c:/boot/grub
mcopy /usr/lib/grub/i386-pc/stage1 c:/boot/grub
mcopy /usr/lib/grub/i386-pc/stage2 c:/boot/grub
mcopy /usr/lib/grub/i386-pc/fat_stage1_5 c:/boot/grub
echo "(hd0) core.img" > bmap
printf "geometry (hd0) 88 16 63 \n root (hd0,0) \n setup (hd0)\n" | /usr/sbin/grub --device-map=bmap --batch
mcopy ./grub/menu.lst c:/boot/grub/
mcopy kernel.bin c:/boot/grub/
qemu-system-i386 -hda core.img
rm kernel.bin
rm bmap
rm core.img
