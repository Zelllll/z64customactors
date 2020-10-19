# toolchain
CC      = mips64-gcc
LD      = mips64-ld
OBJCOPY = mips64-objcopy
OBJDUMP = mips64-objdump

# skelanime_change_link_anim's ram address
ADDRESS = 0x800D8408

# default compilation flags
CFLAGS = -G 0 -O2 --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = --emit-relocs -T
LDFLAGS = -L$(Z64OVL_LD) -T z64ovl.ld --emit-relocs

default: skelanime_change_link_anim.bin

skelanime_change_link_anim.bin:
	@echo -n "ENTRY_POINT = " > entry.ld
	@echo -n $(ADDRESS) >> entry.ld
	@echo -n ";" >> entry.ld
	@$(CC) -c skelanime_change_link_anim.c $(CFLAGS)
	@$(LD) -o skelanime_change_link_anim.elf skelanime_change_link_anim.o $(LDFLAGS) $(LDFILE)
	@$(OBJCOPY) -R .MIPS.abiflags -O binary skelanime_change_link_anim.elf skelanime_change_link_anim.bin
	@$(OBJDUMP) -t skelanime_change_link_anim.elf | grep code1

clean:
	rm -f *.bin *.elf *.o
