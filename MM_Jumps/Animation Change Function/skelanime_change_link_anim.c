#include <z64ovl/oot/debug.h>

extern func_800A3B8C(z64_skelanime_t* skelAnime);
asm("func_800A3B8C = 0x800A3B8C");

extern void SkelAnime_CopyVec3s(z64_skelanime_t* skelAnime, vec3s_t* dst, vec3s_t* src);
asm("SkelAnime_CopyVec3s = 0x800A5774");

extern void SkelAnime_LoadLinkAnimetion(z64_global_t* globalCtx, z64_animation_entry_link_t* linkAnimetionSeg, s32 frame,
                                 s32 limbCount, void* ram);
asm("SkelAnime_LoadLinkAnimetion = 0x800A336C");

extern s16 SkelAnime_GetTotalFrames(void* animationSeg);
asm("SkelAnime_GetTotalFrames = 0x800A1FC8");

extern s32 func_800A3BE4(z64_global_t* globalCtx, z64_skelanime_t* skelAnime);
asm("func_800A3BE4 = 0x800A3BE4");

#define ANIM_JUMP           0x04003148
#define ANIM_FRFL           0x04002B78
#define ANIM_CTWL           0x04002B88

extern s32 lastJumpPtr;
asm("lastJumpPtr = 0x800D812C");

extern s8 jumpIdx;
asm("jumpIdx = 0x800D8130");

u32 jumpAnims[] = {
    ANIM_JUMP, ANIM_FRFL, ANIM_CTWL
};

void code1_SkelAnime_ChangeLinkAnim
(z64_global_t* globalCtx, z64_skelanime_t* skelAnime, z64_animation_entry_link_t* linkAnimetionEntrySeg,
                                    f32 playbackSpeed, f32 frame, f32 frameCount, u8 animationMode, f32 transitionRate) {
    
    // MM Link jumps
    if (linkAnimetionEntrySeg == ANIM_JUMP) {    
        // Set the jump pointer
        linkAnimetionEntrySeg = jumpAnims[jumpIdx];

        // Correct the frame count argument
        frameCount = z_skelanime_anim_nframes(linkAnimetionEntrySeg);

        // Store the last jump pointer
        lastJumpPtr = linkAnimetionEntrySeg;
    }

    skelAnime->mode = animationMode;
    if ((transitionRate != 0.0f) &&
        ((linkAnimetionEntrySeg != skelAnime->anim_current.link_animetion_seg) || (frame != skelAnime->anim_current_frame))) {
        if (transitionRate < 0) {
            func_800A3B8C(skelAnime);
            SkelAnime_CopyVec3s(skelAnime, skelAnime->transition_draw_table, skelAnime->limb_draw_table);
            transitionRate = -transitionRate;
        } else {
            skelAnime->anim_update = &func_800A3BE4;
            SkelAnime_LoadLinkAnimetion(globalCtx, linkAnimetionEntrySeg, (s32)frame, skelAnime->limb_count,
                                        skelAnime->transition_draw_table);
        }
        skelAnime->trans_current_frame = 1.0f;
        skelAnime->transition_step = 1.0f / transitionRate;
    } else {
        func_800A3B8C(skelAnime);
        SkelAnime_LoadLinkAnimetion(globalCtx, linkAnimetionEntrySeg, (s32)frame, skelAnime->limb_count,
                                    skelAnime->limb_draw_table);
        skelAnime->trans_current_frame = 0.0f;
    }

    skelAnime->anim_current.link_animetion_seg = linkAnimetionEntrySeg;
    skelAnime->anim_current_frame = 0.0f;
    skelAnime->start_frame = frame;
    skelAnime->anim_current_frame = frame;
    skelAnime->anim_frame_count = frameCount;
    skelAnime->anim_frame_total = SkelAnime_GetTotalFrames(linkAnimetionEntrySeg);
    skelAnime->anim_playback_speed = playbackSpeed;
}