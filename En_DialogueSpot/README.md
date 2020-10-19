# Z-Targetable Textbox Spot
This is a simple actor which spawns a Z-targetable spot, which the player can then interact with.
This may be useful, because it allows you to use any text ID, rather than in OoT where this actor only had a few hardcoded options.

## Actor variable format:
XXXX; X = Text ID (Values can be found here: https://wiki.cloudmodding.com/oot/Text_IDs)
Z Rotation = YYYY; Y = Z Target Distance; Setting this to 0 gives a typical target distance, test other values for other distances.

### How to use:
**Before using this actor, make sure to edit the values at the top of the .c file to be correct!**
To change the ROM version, open checkabletextspot.c, and change `<z64ovl/oot/debug.h>` to `<z64ovl/oot/u10.h>` if using Ocarina of Time 1.0, or `<z64ovl/mm/u10.h>` if using Majora's Mask 1.0. (OoT Debug is used by default).

To use this actor, open `z_en_dialoguespot.c` then inject the .c with Nokaubure's Custom Actors Toolkit.
Before compiling, make sure to select **Help > Download Z64OVL Github** in Custom Actors Toolkit.
