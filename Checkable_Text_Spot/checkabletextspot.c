/**
 * checkabletextspot.c
 *
 * A Z-targetable text box spot.
 *
 * by zel.
 **/
 
#include <z64ovl/oot/debug.h> /* Change to this to oot/u10.h for OoT 1.0, or mm/u10.h for MM 1.0.

#define ACT_ID                  0x012C /* Change this to the ID of the actor that you are replacing. */
#define OBJ_ID                  0x0001
#define FLAGS                   0x00000011
#define ACT_TYPE                OVLTYPE_PROP

typedef struct {
    z64_actor_t actor;
} Actor;                    

void Init(Actor* this, z64_global_t* globalCtx);
void Destroy(Actor* this, z64_global_t* globalCtx);
void Update(Actor* this, z64_global_t* globalCtx);

z64_actor_init_t init_vars = {
    ACT_ID,
    ACT_TYPE,
    0,
    FLAGS,
    OBJ_ID,
    0,
    sizeof(Actor),
    Init,
    Destroy,
    Update,
    NULL
};

void Init(Actor* this, z64_global_t* globalCtx) {
    // Set the message ID to the actor's params
    this->actor.text_id = this->actor.variable;
    
    // Set the Z target distance
    this->actor.target_dist_index = this->actor.rot.z;
}

void Destroy(Actor* this, z64_global_t* globalCtx) {
}

void Update(Actor* this, z64_global_t *globalCtx) {
    if (this->actor.xz_dist_from_link < 100.0f) {
        // Enable speak command
        external_func_8002F2F4(&this->actor, globalCtx);
    }
}
