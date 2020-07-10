# Majora's Mask Link Jump animations in Ocarina of Time (MQ DBG Only)
This is an assembly hack that adds two new alternate jump animations to Ocarina of Time
from Majora's Mask. This is similar to an old hack by [CrookedPoe](https://github.com/CrookedPoe/),
however it fixes some issues, such as it not being compatible with compression, or various tools such as
ZZROMTool and ZZRTL. Not only that, but this new version requires the player to quickly jump between platforms,
or the alternate animation will not play.

## Compilation:
In order to compile these hacks, it will require [z64ovl](https://https://github.com/z64me/z64ovl/), and glankk's [N64 Toolchain](https://github.com/glankk/n64).
You will also need to manually edit the assembly pointers to the address of the functions.

### How to use:
In order to use this hack, simply drag and drop `patch.txt` and a clean Ocarina of Time Master Quest Debug ROM,
into [Cloudmax's ROM Patcher](https://cloudmodding.com/app/rompatcher).
