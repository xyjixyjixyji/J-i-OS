B=boot
K=kernel
U=user

.PHONY: clean run

run:
	make -C $B
	make -C $K
	cp ./$B/boot ./os.img
	cat $K/kernel >> ./os.img
	
	qemu-system-x86_64 -drive format=raw,file=os.img

clean:
	rm -rf */.o $K/*.o $K/*.elf $K/kernel $B/boot *.img

