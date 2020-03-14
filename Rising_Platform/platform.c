/**
 * platform.c
 *
 * A rising and falling platform.
 *
 * by /zel/
 *
 * Thanks to z64.me for help with the Update function!
 **/
 
#include <z64ovl/oot/debug.h> 
#include "obj.h"
#include <z64ovl/helpers.h>

typedef struct {
	z64_actor_t actor;
    z64_dynapoly_t dynapoly;
    z64_actor_t *link;
    float highPos;
    float lowPos;
    int moving;
    int nextDirection;
} entity_t;

#define OVL_TYPE                    OVLTYPE_BG

void Init(entity_t *this, z64_global_t *global);
void Destroy(entity_t *this, z64_global_t *global);
void Update(entity_t *this, z64_global_t *global);
void Draw(entity_t *this, z64_global_t *global);

const z64_actor_init_t init_vars = 
{
	.number = ACT_ID, .padding = 0x0000,
	.type = OVL_TYPE,
	.room = 0x00,
	.flags = 0x00000010,
	.object = OBJ_ID,
	.instance_size = sizeof(entity_t),
	.init = Init,
	.dest = Destroy,
	.main = Update,
	.draw = Draw
};

uint32_t initChain[] =
{
	ICHAIN(ICHAIN_VEC3Fdiv1000, scale, 100),
	ICHAIN(ICHAIN_F, draw_distance, 3000),
	ICHAIN(ICHAIN_F, camera_clip_near, 500),
	ICHAIN(ICHAIN_F, camera_clip_far, 1000) & ICHAIN_LAST
};

void Init(entity_t *this, z64_global_t *global)
{
	uint32_t temp = 0;

	z_lib_ichain_init(&this->actor, initChain);

    actor_dynapoly_set_move(&this->actor, 1);
    dynapoly_alloc(COL_PLATFORM, &temp);
    this->dynapoly.polyID = actor_register_dynapoly(global, AADDR(global, 0x810), &this->actor, temp);
    
    this->moving = 0;
    this->nextDirection = 0;

    this->lowPos = this->actor.pos_2.y;
    this->highPos = this->lowPos + this->actor.variable;

    this->link = &zh_get_player(global)->actor;
}

void Destroy(entity_t *this, z64_global_t *global)
{
    dynapoly_free(global, AADDR(global, 0x810), this->dynapoly.polyID);
}

void Update(entity_t *this, z64_global_t *global)
{
    if (this->dynapoly.flags & 2 || this->actor.pos_2.y > this->lowPos && this->link->pos_2.y < (this->highPos - 50))
    {
        if (this->moving == 0)
        {
            if (this->nextDirection)
            {
                this->moving = this->nextDirection;
            }
            else
            {
                this->moving = 1;
            }       
        }
    }
    else if (this->moving == 2)
    {
        this->moving = 0;
    }

    if (this->moving == 1 && (this->dynapoly.flags & 2))
    {
        this->actor.pos_2.y += 10;
        sound_play_actor2(&this->actor, SFX_ID);
        if (this->actor.pos_2.y >= this->highPos)
        {
            this->actor.pos_2.y = this->highPos;
            this->nextDirection = -1;
            this->moving = 2;
        }
    }
    else if (this->moving == -1 || ((this->actor.pos_2.y > this->lowPos) && (this->link->pos_2.y < (this->highPos - 50))))
    {
        this->actor.pos_2.y -= 10;
        sound_play_actor2(&this->actor, SFX_ID);
        if (this->actor.pos_2.y <= this->lowPos)
        {
            this->actor.pos_2.y = this->lowPos;
            this->nextDirection = 1;
            this->moving = 2;
        }
    }

    if (this->dynapoly.flags & 2)
    {
        set_camera_id(AADDR(global, 0x1E0), CAMERA_ID);
    }
}

void Draw(entity_t *this, z64_global_t *global)
{
    draw_dlist_opa(global, DL_PLATFORM);
}
