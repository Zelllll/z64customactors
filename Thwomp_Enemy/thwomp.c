/**
 * thwomp.c
 *
 * A custom Thwomp enemy!
 *
 * by /zel/
 **/
 
#include <z64ovl/oot/debug.h> 
#include "obj.h"
#include <z64ovl/helpers.h>

typedef struct {
	z64_actor_t actor;
    z64_dynapoly_t dynapoly;
    z64_collider_cylinder_main_t cylinder;
    uint8_t state;
    uint32_t timer;
    float ogY;
    float newY;
} entity_t;

#define OVL_TYPE                    OVLTYPE_BG

void Init(entity_t *this, z64_global_t *global);
void Destroy(entity_t *this, z64_global_t *global);
void Update(entity_t *this, z64_global_t *global);
void Draw(entity_t *this, z64_global_t *global);
void WaitToRise(entity_t *this);
void WaitToLower(entity_t *this);
void Rise(entity_t *this, z64_global_t *global);
void Lower(entity_t *this, z64_global_t *global);

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

uint32_t cylinderInfo[] =
{
    0x0A110009, 0x20010000, 0x00000000, 0xFFCFFFFF, 
    0x04050000, 0xFFCFFFFF, 0x00000000, 0x01010100,
    0x00230050, 0x00000000, 0x00000000
};

uint32_t initChain[] =
{
    ICHAIN(ICHAIN_Fdiv1000, gravity, 0xFA24),
	ICHAIN(ICHAIN_VEC3Fdiv1000, scale, 7), /* Use 10 normally */
	ICHAIN(ICHAIN_F, draw_distance, 3000) & ICHAIN_LAST
};

void Init(entity_t *this, z64_global_t *global)
{
    uint32_t temp = 0;

	z_lib_ichain_init(&this->actor, initChain);
    
    actor_dynapoly_set_move(&this->actor, 1);
    dynapoly_alloc(COL_THWOMP, &temp);
    this->dynapoly.polyID = actor_register_dynapoly(global, AADDR(global, 0x810), &this->actor, temp);

    z_collider_cylinder_alloc(global, &this->cylinder);
    z_collider_cylinder_init(global, &this->cylinder, &this->actor, &cylinderInfo);
    z_collider_cylinder_update(&this->actor, &this->cylinder);

    this->ogY = this->actor.pos_2.y;
    this->newY = this->actor.pos_2.y + 75;
    this->state = 0;
}

void Destroy(entity_t *this, z64_global_t *global)
{
    dynapoly_free(global, AADDR(global, 0x810), this->dynapoly.polyID);
    z_collider_cylinder_free(global, &this->cylinder);
}

void Update(entity_t *this, z64_global_t *global)
{
    z_actor_find_bounds(global, &this->actor, 15.0f, 50.0f, 60.0f, 0x1D);
    z_collider_set_at(global, AADDR(global, 0x11E60), &this->cylinder);

    switch (this->state)
    {
        case 1:
            this->timer = 0;
            Rise(this, global);
            break;
        case 2:
            WaitToLower(this);
            break;
        case 3:
            this->timer = 0;
            Lower(this, global);
            break;
        /* state 0 */
        default:
            this->cylinder.y_shift = -400; /* moves cylinder below the map so it can't touch Link */
            WaitToRise(this);
            break;
    }
}

void Draw(entity_t *this, z64_global_t *global)
{
    z_draw_dlist_opa(global, DL_THWOMP);

    f32 circleSize[] = {1.15f, 0.0f, 1.15f};
    actor_shadow_circle(&this->actor.pos_2, circleSize, 0xFF, global);
}

void WaitToRise(entity_t *this)
{
    this->timer ++;
    if (this->timer > 15)
    {
        this->state = 1;
    }
}

void WaitToLower(entity_t *this)
{
    this->timer ++;
    if (this->timer > 20)
    {
        this->state = 3;
    }
}

void Rise(entity_t *this, z64_global_t *global)
{
    this->actor.vel_1.y = 3.5f;
    this->actor.vel_1.y += 0.2f;
    z_actor_move_dir_vel(&this->actor);

    if (this->actor.pos_2.y >= this->newY)
    {
        this->actor.pos_2.y = this->newY;
        this->state = 2;
    }
}

void Lower(entity_t *this, z64_global_t *global)
{
    this->actor.vel_1.y = -10.0f;
    this->actor.vel_1.y -= 0.4f;
    z_actor_move_dir_vel(&this->actor);

    if (this->actor.pos_2.y <= this->ogY)
    {
        this->cylinder.y_shift = 0;
        this->actor.pos_2.y = this->ogY;
        if (this->actor.dist_from_link_xz < 1500.0f)
        {
            camera_earthquake(AADDR(global, 0x1E0), 2, 1, 20);
            sound_play_actor2(&this->actor, SFX_ID);
        }
        this->state = 0;
    }  
}
