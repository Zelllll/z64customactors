# Configurable Rising Platform
**Special thanks to z64.me for helping with some of the logic in this actor!**

This is a rising elevator platform; perfect for dungeon puzzles. The model, as well as other parameters can be easily changed in `obj.h` as well.
The platform will also automatically lower if it is in a location that is inaccessible to the player. The amount which the platform should rise can also be configured with the actor variable.

## Actor variable format:
XXXX; X = Amount of units for the platform to raise (in hexadecimal)

### How to use:
**Before using this actor, make sure to edit the values in obj.h to be correct!**
To change the ROM version, open `platform.c`, and change `<z64ovl/oot/debug.h>` to `<z64ovl/oot/u10.h>` if using Ocarina of Time 1.0, or `<z64ovl/mm/u10.h>` if using Majora's Mask 1.0. (OoT Debug is used by default).

To use this actor, make sure `obj.h` (this file) and `platform.c` are in the same folder, then inject the .c with Nokaubure's Custom Actors Toolkit.
Also, before compiling, make sure to select **Help > Download Z64OVL Github** in Custom Actors Toolkit.
