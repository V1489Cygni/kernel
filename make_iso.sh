#xorriso required!
make
mkdir -p temp
mkdir -p temp/boot
cp kernel.bin temp/boot/kernel.bin
mkdir -p temp/boot/grub
cp ./grub/grub.cfg temp/boot/grub/grub.cfg
grub-mkrescue -o image.iso temp
rm -rf temp
