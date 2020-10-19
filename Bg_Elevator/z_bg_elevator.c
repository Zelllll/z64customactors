/**
 * z_en_elevator.c
 * 
 * A rising and falling platform.
 * 
 * by zel.
*/
 
#include <z64ovl/oot/debug.h>                       /* Change to this to oot/u10.h for OoT 1.0, or mm/u10.h for MM 1.0. */

// Actor initialization information
#define ACT_ID                  0x012C              /* Change this to the ID of the actor that you are replacing.
                                                       or change it to 0xDEAD for ZZRTL, then remove the "ivar"
                                                       line from conf.txt. */

#define OBJ_ID                  0x011D              /* Change this to the ID of the object that you are replacing. */

#define ACT_TYPE                OVLTYPE_BG          /* This is the actor's category. BG is used for actors that have
                                                       polygon collision, because without it the player will clip
                                                       through the elevator. */

#define FLAGS                   0x00000010          /* These flags control various properties of the actor, do not
                                                       worry about changing them. */

#define PAD                     0                   /* Change this to 0xBEEF for ZZRTL. */

// Displaylists
#define DL_PLATFORM             0x060021B0          /* Address to the platform model, do not change if you use the
                                                       provided object. */

// Collisions
#define COL_PLATFORM            0x06001400          /* Address to the platform collision, do not change if you use
                                                       the provided object. */

// SFX
#define SFX_ID                  0x2024              /* Sound effect to play when the platform rises/falls, if you wish
                                                       to change it, check the values here:
                                                       https://wiki.cloudmodding.com/oot/Sound_Effect_Ids . */

// Camera
#define CAMERA_ID               0                   /* Camera ID in your custom map to use when Link stands on the
                                                       platform. The value can be left at 0 if you wish to use the
                                                       default camera inside your map however. */


/* This is the actor's instance structure. The z64_actor_t type is always required first, anything else is optional
   variables. These are independent to each actor's instance, rather than global variables which will affect all of
   the instances of an actor spawned in a scene. */
typedef struct {
    z64_actor_t actor;
    z64_dynapoly_t dynapoly;
    f32 posMin;
    f32 posMax;
    s16 movingState;
    s16 directionState;
} Actor;

void Init(Actor* this, z64_global_t* globalCtx);
void Destroy(Actor* this, z64_global_t* globalCtx);
void Update(Actor* this, z64_global_t* globalCtx);
void Draw(Actor* this, z64_global_t* globalCtx);

/* This is the actor's initialization variables, which are controlled through the macros above. */
const z64_actor_init_t init_vars = {
    ACT_ID,
    ACT_TYPE,
    0,
    FLAGS,
    OBJ_ID,
    PAD,
    sizeof(Actor),
    Init,
    Destroy,
    Update,
    Draw
};

/* These are extra intialization variables, so things like the scale and draw distance can
   be set without having to manually set them. These will be set when z_lib_ichain_init is used */
static u32 sInitChain[] = {
    ICHAIN(ICHAIN_VEC3Fdiv1000, scale, 100),
    ICHAIN(ICHAIN_F, draw_dist, 3000),
    ICHAIN(ICHAIN_F, cam_clip_near, 500),
    ICHAIN(ICHAIN_F, cam_clip_far, 1000) & ICHAIN_LAST
};

void Init(Actor* this, z64_global_t* globalCtx) {
    z_lib_ichain_init(&this->actor, sInitChain);
    
    // Initialize collision
    actor_dynapoly_set_move(&this->actor, DPM_PLAYER);
    z_dynapoly_new(globalCtx, &this->actor, COL_PLATFORM);
    
    // Set initial values for instance variables
    this->movingState = this->directionState = 0;
    this->posMin = this->actor.pos.y;
    this->posMax = this->posMin + (f32)this->actor.variable;
}

void Destroy(Actor* this, z64_global_t* globalCtx) {
    // Destroy collision
    DynaPolyInfo_Free(globalCtx, &globalCtx->col_ctxt.unk_00_, this->dynapoly.poly_id);
}

#define DYNA_PLAYER_ON_TOP (this->dynapoly.flags & 2)
#define PLAYER globalCtx->actor_ctxt.actor_list[OVLTYPE_PLAYER].first

void Update(Actor* this, z64_global_t* globalCtx) {
    z64_player_t* player = PLAYER;
    
    if (DYNA_PLAYER_ON_TOP || this->actor.pos.y > this->posMin && player->actor.pos.y < this->posMax - 50) {
        if (this->movingState == 0) {
            if (this->directionState) {
                this->movingState = this->directionState;
            } else {
                this->movingState = 1;
            }       
        }
    } else if (this->movingState == 2) {
        this->movingState = 0;
    }

    if (this->movingState == 1 && DYNA_PLAYER_ON_TOP) {
        // Rise
        this->actor.pos.y += 10.0f;
        Audio_PlayActorSound2(&this->actor, SFX_ID);

        if (this->actor.pos.y >= this->posMax) {
            this->actor.pos.y = this->posMax;
            this->directionState = -1;
            this->movingState = 2;
        }
    } else if (this->movingState == -1 || this->actor.pos.y > this->posMin && player->actor.pos.y < this->posMax - 50) {
        // Fall
        this->actor.pos.y -= 10.0f;
        Audio_PlayActorSound2(&this->actor, SFX_ID);
        
        if (this->actor.pos.y <= this->posMin) {
            this->actor.pos.y = this->posMin;
            this->directionState = 1;
            this->movingState = 2;
        }
    }

    if (DYNA_PLAYER_ON_TOP) {
        // Set camera whenever the player is standing on the elevator
        set_camera_id(&globalCtx->camera[0], CAMERA_ID);
    }
}

void Draw(Actor* this, z64_global_t* globalCtx) {
    // Draw the elevator model
    Gfx_DrawDListOpa(globalCtx, DL_PLATFORM);
}
