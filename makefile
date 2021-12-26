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
SIZE = 1500K

# binaries
BINS = $(OBJS:.o=.bin)

.PHONY : clean

# runs the emulator with the desired drive
all: clean $(IMGDIR)$(IMAGE).img

# creates the final image file, truncating to size
$(IMGDIR)$(IMAGE).img : $(OBJDIR)boot.bin $(BINS)
	cat $^ > $@
	truncate -s $(SIZE) $@

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
