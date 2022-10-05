# Set the C compiler and debugger
CC = clang
GDB = gdb 

LD = /usr/local/Cellar/llvm/12.0.1/bin/ld.lld
ASM = nasm

INC = -Iinc/
SRC = $(shell find . -type f -name "*.c")
ASM_SRC = $(shell find . -type f -name "*.S")

OBJ = ${ASM_SRC:.S=.o} ${SRC:.c=.o} 

CCFLAGS = -ggdb -c -ffreestanding -fomit-frame-pointer -Werror -target x86_64-none-elf
# LDFLAGS = -Ttext 0x8200
LDFLAGS = -Tkernel.ld
LDFLAGS_BIN = ${LDFLAGS} --oformat binary
ASFLAGS = -f elf64

all: kernel kernel.elf

kernel: ${OBJ}
	${LD} -o $@ ${LDFLAGS_BIN} $^

kernel.elf: ${OBJ}
	${LD} -o $@ ${LDFLAGS} $^

%.o: %.c
	${CC} ${CCFLAGS} ${INC} -o $@ $^

%.o: %.S
	${ASM} $< ${ASFLAGS} -o $@

clean:
	rm -f kernel kernel.elf *.o **/*.o
