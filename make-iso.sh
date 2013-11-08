#Xorriso required!
./compile.sh
mkdir -p temp
mkdir -p temp/boot
cp kernel.bin temp/boot/kernel.bin
mkdir -p temp/boot/grub
cp ./grub/grub.cfg temp/boot/grub/grub.cfg
grub-mkrescue -o kernel.iso temp
rm -rf temp
rm kernel.bin
