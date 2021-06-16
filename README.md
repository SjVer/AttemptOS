# AttemptOS
A baremetal OS for x86_64 <br/><br/>
### What is it?
AttemptOS is an attempt at making a simple OS. It is probebly just awfull but I guess it's fun to make so yea.
<br/>
PS: Like any decent makefile you can easily change up stuff like the compiler and terminal emulator n shit so yea.
<br/><br/>
### Makefile
The makefile includes the following targets:
- elf: builds the kernel.elf file
- run-elf: runs that elf file
- iso: builds the attemptos.iso file
- run-iso: you guessed it
- mkdirs: prepares the iso directory
- check: this is dumb
- run-debug: runs the elf file with debugging shit
- clean: cleans up
- git-push: handy git stuff for me :)
<br/><br/>
### Deps n shit
The dependencies for this project are:
- qemu-system
- genisoimage
- gcc
- ld
- gdb-multiarch
- make (mindblow)