nasm -f elf -o loader.o ./loader/loader.asm
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o service.o ./service/service.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o output.o ./output/output.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o input.o ./input/input.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o shell.o ./shell/shell.c
gcc -fno-stack-protector -fno-builtin -nostdinc -O -g -Wall -I. -std=c99 -c -o kernel.o ./kernel/kernel.c
ld -T link.ld -o kernel.bin loader.o  service.o output.o input.o shell.o kernel.o
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
