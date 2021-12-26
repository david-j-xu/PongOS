CC = gcc
CFLAGS = -ffreestanding

# C header files
SRCS = $(wildcard src/kernel/*.c)

# object files list
OBJDIR = build/
OBJS = $(addprefix $(OBJDIR), $(notdir $(SRCS:.c=.o)))

# image properties
IMGDIR = images/
IMAGE = PongOS
NUM_BLOCKS = 3000

# binaries
BINS = $(OBJS:.o=.bin)

.PHONY : clean

# runs the emulator with the desired drive
all: clean $(IMGDIR)$(IMAGE).img

# creates the final image file, filling NUM_BLOCKS blocks
$(IMGDIR)$(IMAGE).img: $(OBJDIR)os-img
	dd if=$^ of=$@ bs=512 count=$(NUM_BLOCKS)

# creates intermediate image file
$(OBJDIR)os-img : $(OBJDIR)boot.bin $(BINS)
	cat $^ > $@

# creates binary files from compiled object files
$(OBJDIR)%.bin : build/%.o
	ld -o $@ -Ttext 0x1000 $^ --oformat=binary

# creates object files
$(OBJDIR)%.o : src/kernel/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

# cleans build files and images
clean:
	rm -rf $(OBJDIR)* $(IMGDIR)*

# builds the boot sector
$(OBJDIR)boot.bin: src/boot/boot.asm
	nasm $< -f bin -o $@

# runs the os
run: $(IMGDIR)$(IMAGE).img
	qemu-system-i386 -drive format=raw,file=$^ \
		-display curses \
		-serial mon:stdio \
		-monitor telnet:127.0.0.1:54321,server,nowait

# Opens up a monitor
monitor:
	telnet 127.0.0.1 54321
