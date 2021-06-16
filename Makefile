# customiseable stuff
NAME = attemptos
CC = gcc #x86_64-elf-gcc
LD = ld #x86_64-elf-ld
GDB = /usr/bin/gdb-multiarch
TERMINAL = x-terminal-emulator  

# dirs
SRCDIR=./src
BINDIR=./bin
DEPDIR=$(BINDIR)/deps
OBJDIR=$(BINDIR)/obj

# flags
TERMFLAGS = -e
WARNINGS = -Wall -W -Wstrict-prototypes -Wmissing-prototypes -Wsystem-headers
CFLAGS = -g -msoft-float -O -fno-stack-protector
CPPFLAGS = -nostdinc -I$(SRCDIR) -I$(SRCDIR)/lib -I$(SRCDIR)/lib/kernel  -I$(SRCDIR)/devices
ASFLAGS = -Wa,--gstabs
LDFLAGS = -T $(SRCDIR)/link.ld -melf_i386

# functions
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

# files
SOURCES = $(call rwildcard,$(SRCDIR),*.c *.S)
OBJECTS = $(addsuffix .o, $(basename $(SOURCES))) # $(patsubst %.c,%.o,$(patsubst %.S,%.o,$(SOURCES)))
DEPS = -MMD -MF $(addprefix $(DEPDIR)/,$(notdir $(@:.o=.d)))

# targets
all: mkdirs elf iso
%.o: %.c
	@printf "compiling $<..."
	@$(CC) -m32 -c $< -o $(OBJDIR)/$(notdir $@) $(CFLAGS) $(CPPFLAGS) $(WARNINGS) $(DEFINES) $(DEPS) -w
	@printf "\b\b done!\n"

%.o: %.S
	@printf "compiling $<..."
	@$(CC) -m32 -c $< -o $(OBJDIR)/$(notdir $@) $(ASFLAGS) $(CPPFLAGS) $(DEFINES) $(DEPS)
	@printf "\b\b done!\n"

elf: mkdirs $(OBJECTS)
	@printf "linking objects..."
	@$(LD) $(LDFLAGS) $(addprefix $(OBJDIR)/, $(notdir $(OBJECTS))) -o $(BINDIR)/kernel.elf
	@printf "\b\b done!\n"

iso: mkdirs
	@if ! [ -f $(BINDIR)/kernel.elf ]; then \
		echo "$(BINDIR)/kernel.elf does not exist. Making it first..."; \
		make elf; echo "Making $(BINDIR)/kernel.elf done!"; fi

	@printf "preparing iso directory and files..."
	
	@mkdir -p $(BINDIR)/iso/boot/grub
	@cp $(BINDIR)/kernel.elf $(BINDIR)/iso/boot/kernel.elf
	@cp stage2_eltorito $(BINDIR)/iso/boot/grub/
	@cp menu.lst $(BINDIR)/iso/boot/grub
	@printf "\b\b done!\n"

	@printf "generating iso file..."
	@genisoimage -R                              \
				-b boot/grub/stage2_eltorito    \
				-no-emul-boot                   \
				-boot-load-size 4               \
				-A os                           \
				-input-charset utf8             \
				-quiet                          \
				-boot-info-table                \
				-o $(BINDIR)/$(NAME).iso        \
				$(BINDIR)/iso
	@printf "\b\b done!\n"

clean:
	@rm -rf $(BINDIR)
check:
	@printf "Sources:\n"
	@printf "\t$(SOURCES)\n"
	@printf "Objects:\n"
	@printf "\t$(addprefix $(OBJDIR), $(notdir $(OBJECTS)))\n"
	@printf "Dependencies:\n"
	@printf "\t$(DEPS)\n"
	@printf "Tools:\n"
	@printf "\t`which $(CC)`\n"
	@printf "\t`which $(LD)`\n"
mkdirs:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(DEPDIR)

run-elf:
	@if ! [ -f $(BINDIR)/kernel.elf ]; then \
		echo "$(BINDIR)/kernel.elf does not exist. Making it first..."; \
		make elf; echo "Making $(BINDIR)/kernel.elf done!"; fi
	@echo "Running kernel.elf using qemu-system-x86_64..."
	@qemu-system-x86_64 -kernel $(BINDIR)/kernel.elf $(args) -show-cursor

run-debug:
	@echo "Running kernel.elf using qemu-system-x86_64 in debug mode..."
	@$(TERMINAL) $(TERMFLAGS) $(GDB) $(BINDIR)/kernel.elf -x=./gdbinit &
	@qemu-system-x86_64 -show-cursor -kernel $(BINDIR)/kernel.elf -s -S $(args)

run-iso:
	@echo "Running $(NAME).iso using qemu-system-x86_64"
	@qemu-system-x86_64 -cdrom $(BINDIR)/$(NAME).iso -monitor stdio $(args) -show-cursor

git-push:
	@echo "Adding, committing and pushing to github..."
	@git add --all
	@git commit -m upload
	@git push origin main
	@echo "Done!"