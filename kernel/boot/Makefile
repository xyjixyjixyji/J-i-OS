boot : boot.S
	nasm -f bin boot.S -o boot

qemu : boot
	qemu-system-x86_64 -fda boot

clean :
	rm -rf boot
