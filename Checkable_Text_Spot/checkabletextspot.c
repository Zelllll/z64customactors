/**
 * checkabletextspot.c
 *
 * A Z-targetable text box spot.
 *
 * by /zel/
 **/
 
#include <z64ovl/oot/debug.h> 
#include "obj.h"

typedef struct
{
	z64_actor_t actor;
} entity_t;

#define OVL_TYPE                    OVLTYPE_PROP

void Init(entity_t *this, z64_global_t *global);
void Destroy(entity_t *this, z64_global_t *global);
void Update(entity_t *this, z64_global_t *global);
void Draw(entity_t *this, z64_global_t *global);

const z64_actor_init_t init_vars = 
{
	.number = ACT_ID, .padding = 0x0000,
	.type = OVL_TYPE,
	.room = 0x00,
	.flags = 0x00000011,
	.object = OBJ_ID,
	.instance_size = sizeof(entity_t),
	.init = Init,
	.dest = Destroy,
	.main = Update,
	.draw = Draw
};

void Init(entity_t *this, z64_global_t *global)
{
    this->actor.text_id = this->actor.variable;
    this->actor.target_dist_index = this->actor.rot.z;
}

void Destroy(entity_t *this, z64_global_t *global)
{
    
}

void Update(entity_t *this, z64_global_t *global)
{
    external_func_8002F2F4(&this->actor, global);
}

void Draw(entity_t *this, z64_global_t *global)
{
    
}
