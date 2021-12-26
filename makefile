
# runs the emulator with the desired drive
all: boot.bin
	qemu-system-i386 -drive format=raw,file=build/boot.bin \
	-monitor telnet:127.0.0.1:54321,server,nowait

# builds the boot sector
boot.bin: src/boot/boot.asm
	nasm src/boot/boot.asm -f bin -g -o build/boot.bin

# Opens up a monitor
monitor:
	telnet 127.0.0.1 54321
