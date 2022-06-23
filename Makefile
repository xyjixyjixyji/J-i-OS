B=boot
K=kernel
U=user

QEMU=qemu-system-x86_64

QEMUARGS = -drive format=raw,file=os.img \
		   -device isa-debug-exit,iobase=0xf4,iosize=0x04 \
		   -serial stdio

QEMUTESTARGS = $(QEMUARGS) -display none

.PHONY: qemu sz lldb clean

qemu: img
	$(QEMU) $(QEMUARGS)

test: img
	$(QEMU) $(QEMUTESTARGS)

# dd if=/dev/zero of=os.img bs=512 count=8192
# dd if=boot/boot of=os.img bs=512 conv=notrunc
# dd if=kernel/kernel of=os.img bs=512 seek=3 conv=notrunc
img:
	make clean
	make -C $B && make -C $K
	cp $B/boot ./os.img && cat $K/kernel >> os.img

BYTESZ=$(shell wc -c < os.img)
sz:
	@echo "Byte=$(BYTESZ)"

lldb:
	$(QEMU) $(QEMUARGS) -s -S & \
    lldb -ex "target remote localhost:1234" -ex "symbol-file kernel/kernel.elf"

clean:
	rm -rf */.o $K/*.o $K/*.elf $K/kernel $B/boot *.img

