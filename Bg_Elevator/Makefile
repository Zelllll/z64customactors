PROGRAM = z_bg_elevator
OVLOUT = Bg_Elevator.zovl
ADDRESS = 0x80800000
PARTS = $(PROGRAM).o

CC   = mips64-gcc
LD   = mips64-ld
NOVL = novl

CFLAGS = -G 0 -Os -fno-reorder-blocks -std=gnu99 -mtune=vr4300 -march=vr4300 -mabi=32 -c -mips3 -mno-explicit-relocs -mno-memcpy -mno-check-zero-division
LDFLAGS = -T /opt/n64/mips64/include/z64ovl/z64ovl.ld --emit-relocs
NOVLFLAGS = -vvv -c -A $(ADDRESS) -o $(OVLOUT)

default: $(PROGRAM).ovl

$(PROGRAM).ovl: $(PARTS)
	$(LD) -o $(PROGRAM).elf $(PARTS) $(LDFLAGS)
	$(NOVL) $(NOVLFLAGS) $(PROGRAM).elf

clean:
	rm -fv $(PROGRAM).elf $(OVLOUT) $(PARTS)
