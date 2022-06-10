boot : boot.S
	nasm -f bin boot.S -o boot.bin

qemu : boot
	qemu-system-x86_64 boot.bin

clean :
	rm -rf *.bin
