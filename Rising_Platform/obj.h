/**
 * obj.h
 *
 * Rising platform information
 *
 * By /zel/
 **/

/** Actor variable format:
 * XXXX; X = Amount of units for the platform to raise (in hexadecimal)
 **/

/* !!!! Credit me if you use this actor somewhere in your mod !!!! */
/* !!!! To use this actor, make sure "obj.h" (this file) and "platform.c" are in the same folder, then inject the .c and .zobj with Nokaubure's Custom Actors Toolkit !!!! */
/* !!!! Before using this actor, open Custom Actors Toolkit, and then select Help > Download Z64OVL Github !!!! */
/* !!!! To change the ROM version, open platform.c, and change "<z64ovl/oot/debug.h>" to "<z64ovl/oot/u10.h>" if using Ocarina of Time 1.0, or "<z64ovl/mm/u10.h>" if using Majora's Mask 1.0. !!!! */

// Actor information
#define ACT_ID                  0x012C              /* Change this to the ID of the actor that you are replacing. */
#define OBJ_ID                  0x011D              /* Change this to the ID of the object that you are replacing. */

// Meshs
#define DL_PLATFORM             0x060021B0          /* Address to the platform model, do not change if you use the provided object */

// Collisions
#define COL_PLATFORM            0x06001400          /* Address to the platform collision, do not change if you use the provided object */

// SFX
#define SFX_ID                  0x2024              /* Sound effect to play when the platform rises/falls, if you wish to change it, check the values here: https://wiki.cloudmodding.com/oot/Sound_Effect_Ids */

// Camera
#define CAMERA_ID               0                   /* Camera ID in your custom map to use when Link stands on the platform; optional! */