# toolchain
CC      = mips64-gcc
LD      = mips64-ld
OBJCOPY = mips64-objcopy
OBJDUMP = mips64-objdump

# jump_control_code's ram address
ADDRESS = 0x800D8134

# default compilation flags
CFLAGS = -G 0 -Ofast --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-check-zero-division -mno-explicit-relocs -mno-memcpy
LDFLAGS = --emit-relocs -T
LDFLAGS = -L$(Z64OVL_LD) -T z64ovl.ld --emit-relocs

default: jump_control_code.bin

jump_control_code.bin:
	@echo -n "ENTRY_POINT = " > entry.ld
	@echo -n $(ADDRESS) >> entry.ld
	@echo -n ";" >> entry.ld
	@$(CC) -c jump_control_code.c $(CFLAGS)
	@$(LD) -o jump_control_code.elf jump_control_code.o $(LDFLAGS) $(LDFILE)
	@$(OBJCOPY) -R .MIPS.abiflags -O binary jump_control_code.elf jump_control_code.bin
	@$(OBJDUMP) -t jump_control_code.elf | grep code1

clean:
	rm -f *.bin *.elf *.o
