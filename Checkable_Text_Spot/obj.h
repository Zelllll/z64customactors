/**
 * obj.h
 *
 * Rising platform information
 *
 * By /zel/
 **/

/** Actor variable format:
 * XXXX; X = Text ID (Values can be found here: https://wiki.cloudmodding.com/oot/Text_IDs)
 *
 * Z Rotation = YYYY; Y = Z Target Distance; Setting this to 0 gives a typical target distance, test other values for other distances.
 **/

/* !!!! Credit me if you use this actor somewhere in your mod !!!! */
/* !!!! To use this actor, make sure "obj.h" (this file) and "checkabletextspot.c" are in the same folder, then inject the .c with Nokaubure's Custom Actors Toolkit !!!! */
/* !!!! Before using this actor, open Custom Actors Toolkit, and then select Help > Download Z64OVL Github !!!! */
/* !!!! To change the ROM version, open checkabletextspot.c, and change "<z64ovl/oot/debug.h>" to "<z64ovl/oot/u10.h>" if using Ocarina of Time 1.0, or "<z64ovl/mm/u10.h>" if using Majora's Mask 1.0. !!!! */

// Actor information
#define ACT_ID                  0x012C              /* Change this to the ID of the actor that you are replacing. */
#define OBJ_ID                  0x011D              /* Change this to the ID of the object that you are replacing. */