/**
 * obj.h
 *
 * Thwomp information
 *
 * By /zel/
 **/

// Actor information
#define ACT_ID                  0x012C              /* Change this to the ID of the actor that you are replacing. */
#define OBJ_ID                  0x011D              /* Change this to the ID of the object that you are replacing. */

// Meshs
#define DL_THWOMP               0x06001EC0          /* Address to the Thwomp model, do not change if you use the provided object */

// Collisions
#define COL_THWOMP              0x06001600          /* Address to the Thwomp collision, do not change if you use the provided object */

// SFX
#define SFX_ID                  0x39B0              /* Sound effect to play when the Thwomp hits the ground, check the values here: https://wiki.cloudmodding.com/oot/Sound_Effect_Ids, use patch if you want the SM64 sound. (Debug only for now) */