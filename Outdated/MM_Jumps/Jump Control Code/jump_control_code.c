#include <z64ovl/oot/debug.h>

#define PLAYER AVAL(globalCtx, uint32_t, 0x1C44)
#define LINK_ANIMATION AVAL(player, uint32_t, 0x1BC)

#define ANIM_JUMP           0x04003148
#define ANIM_FRFL           0x04002B78
#define ANIM_CTWL           0x04002B88

extern s32 lastJumpPtr;
asm("lastJumpPtr = 0x800D812C");

extern s8 jumpIdx;
asm("jumpIdx = 0x800D8130");

uint32_t jumpTimer;

void code1_JumpControl(void) {
    z64_global_t *globalCtx = (z64_global_t *)GLOBAL_CONTEXT;
    z64_player_t *player = PLAYER;

    // Revert to the normal jump after 30 frames
    if (jumpTimer > 30) {
        jumpIdx = 0;
    }
    
    switch (lastJumpPtr) {
        case ANIM_FRFL:
            jumpIdx = 2;
            jumpTimer = 0;
            break;
        case ANIM_CTWL:
            jumpIdx = 0;
            jumpTimer = 0;
            break;
        case ANIM_JUMP:
            jumpIdx = 1;
            jumpTimer = 0;
            break;
        default:
            break;
    }

    lastJumpPtr = NULL;
    
    if (jumpIdx != 0) {
        jumpTimer++;
    }

    if (LINK_ANIMATION == ANIM_JUMP || LINK_ANIMATION == ANIM_FRFL || LINK_ANIMATION == ANIM_CTWL) {
        jumpTimer = 0;
    }
}