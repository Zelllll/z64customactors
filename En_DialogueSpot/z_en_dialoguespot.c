/**
 * z_en_dialoguespot.c
 *
 * A Z-targetable dialogue spot.
 *
 * by zel.
 **/
 
#include <z64ovl/oot/debug.h>                       /* Change to this to oot/u10.h for OoT 1.0, or mm/u10.h for MM 1.0. */

// Actor initialization information
#define ACT_ID                  0x012C              /* Change this to the ID of the actor that you are replacing.
                                                       or change it to 0xDEAD for ZZRTL, then remove the "ivar"
                                                       line from conf.txt. */

#define OBJ_ID                  0x0001              /* Leave this as is since no object is needed. */

#define ACT_TYPE                OVLTYPE_PROP        /* This is the actor's category. */

#define FLAGS                   0x00000011          /* These flags control various properties of the actor, do not
                                                       worry about changing them. The last nyble being 1 enables
                                                       Z-Targetting. */

#define PAD                     0                   /* Change this to 0xBEEF for ZZRTL. */


/* This is the actor's instance structure. The z64_actor_t type is always required first, anything else is optional
   variables. These are independent to each actor's instance, rather than global variables which will affect all of
   the instances of an actor spawned in a scene. */
typedef struct {
    z64_actor_t actor;
} Actor;                    

void Init(Actor* this, z64_global_t* globalCtx);
void Destroy(Actor* this, z64_global_t* globalCtx);
void Update(Actor* this, z64_global_t* globalCtx);

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
    NULL // No Draw function is needed.
};

void Init(Actor* this, z64_global_t* globalCtx) {
    // Set the message ID to the actor's params
    this->actor.text_id = this->actor.variable;
    
    // Set the Z target distance
    this->actor.target_dist_index = this->actor.rot.z;

    // Reset the Z rotation to 0
    this->actor.rot.z = 0;
}

void Destroy(Actor* this, z64_global_t* globalCtx) {
}

void Update(Actor* this, z64_global_t *globalCtx) {
    if (this->actor.xz_dist_from_link < 100.0f) {
        // Enable speak command
        external_func_8002F2F4(&this->actor, globalCtx);
    }
}
