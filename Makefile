# @megstechcorner.com
# All rights reserved.

# customiseable stuff
NAME = attemptos
CC = x86_64-elf-gcc
LD = x86_64-elf-ld
GDB = /bin/gdb-multiarch
TERMINAL = x-terminal-emulator  

# dir stuff
SRCDIR=./src
BINDIR=./bin
DEPDIR=$(BINDIR)/deps
OBJDIR=$(BINDIR)/obj

# flag stuff
WARNINGS = -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers
CFLAGS = -g -msoft-float -O -fno-stack-protector
CPPFLAGS = -nostdinc -I$(SRCDIR) -I$(SRCDIR)/lib -I$(SRCDIR)/lib/kernel 
ASFLAGS = -Wa,--gstabs
LDFLAGS = -T $(SRCDIR)/link.ld -melf_i386
DEPS = -MMD -MF $(addprefix $(DEPDIR)/,$(notdir $(@:.o=.d)))

# functions
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# # Kernel code
# kernel_SRC  = start.S
# kernel_SRC += kmain.c

# # Devices code.
# devices_SRC = devices/vga.c

# # Lib code.
# lib_SRC  = lib/stdio.c
# lib_SRC += lib/string.c
# lib_SRC += lib/arithmetic.c
# lib_SRC += lib/kernel/console.c

# SUBDIRS = kernel devices lib
# SOURCES = $(foreach dir,$(SUBDIRS),$($(dir)_SRC))
# OBJECTS = $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SOURCES)))
# DEPENDS = $(patsubst %.o,%.d,$(OBJECTS))
SOURCES = $(call rwildcard,$(SRCDIR),*.c *.S)
OBJECTS = $(addsuffix .o, $(basename $(SOURCES))) # $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SOURCES)))

# targets
all: mkdirs elf
%.o: %.c
	$(CC) -m32 -c $< -o $(OBJDIR)/$(notdir $@) $(CFLAGS) $(CPPFLAGS) $(WARNINGS) $(DEFINES) $(DEPS)

%.o: %.S
	$(CC) -m32 -c $< -o $(OBJDIR)/$(notdir $@) $(ASFLAGS) $(CPPFLAGS) $(DEFINES) $(DEPS)

elf: mkdirs $(OBJECTS)
	$(LD) $(LDFLAGS) $(addprefix $(OBJDIR)/, $(notdir $(OBJECTS))) -o $(BINDIR)/kernel.elf

iso: mkdirs elf
	mkdir -p $(BINDIR)/iso/boot/grub
	cp $(BINDIR)/kernel.elf $(BINDIR)/iso/boot/kernel.elf
	cp stage2_eltorito $(BINDIR)/iso/boot/grub/
	cp menu.lst $(BINDIR)/iso/boot/grub
	genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o $(BINDIR)/os.is              \
				iso

clean:
	rm -rf $(BINDIR)
check:
	@printf "Sources:\n"
	@printf "\t$(SOURCES)\n"

	@printf "Objects:\n"
	@printf "\t$(addprefix $(OBJDIR), $(notdir $(OBJECTS)))\n"

	@printf "Tools:\n"
	@printf "\t`which $(CC)`\n"
	@printf "\t`which $(LD)`\n"
mkdirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(DEPDIR)
run-elf: kernel.elf
	@qemu-system-x86_64 -kernel $(BINDIR)/kernel.elf $(args)

run-debug: kernel.elf
	@$(TERMINAL) $(TERMFLAGS) $(GDB) $(BINDIR)/kernel.elf -x=./gdbinit &
	@qemu-system-x86_64 -kernel $(BINDIR)/kernel.elf -s -S $(args)

run-iso: iso
	@qemu-system-x86_64 -cdrom $(BINDIR)/$(NAME).iso -monitor stdio $(args)