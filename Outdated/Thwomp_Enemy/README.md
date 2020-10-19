# Custom Thwomp Enemy
This is a completely custom Thwomp enemy! It's behavior closely mimicks its appearance in Super Mario 64 as well.

### How to use:
**Before using this actor, make sure to edit the values in obj.h to be correct!**
To change the ROM version, open thwomp.c, and change `<z64ovl/oot/debug.h>` to `<z64ovl/oot/u10.h>` if using Ocarina of Time 1.0, or `<z64ovl/mm/u10.h>` if using Majora's Mask 1.0. (OoT Debug is used by default).

To use this actor, make sure `obj.h` (this file) and `thwomp.c` are in the same folder, then inject the .c with Nokaubure's Custom Actors Toolkit.
Also, before compiling, make sure to select **Help > Download Z64OVL Github** in Custom Actors Toolkit.

There is also a patch included, which will add the iconic sound effect that the Thwomp uses, however currently I only added the sound to Ocarina of Time Debug,
however I will likely create patches for 1.0 and Majora's Mask at some point. Also note that **this sound effect will replace Koume's laugh**, in
case you are planning on reusing that sound.

To add the patch to your ROM, use a `bps` patcher like [this.](https://www.marcrobledo.com/RomPatcher.js/)
