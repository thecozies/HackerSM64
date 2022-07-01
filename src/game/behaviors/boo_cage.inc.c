
/**
 * Behavior for bhvBooCage.
 * This is the cage inside the big boo in the castle courtyard
 * that lets Mario enter BBH. It has its own special interaction type,
 * INTERACT_BBH_ENTRANCE.
 */

/**
 * Boo cage hitbox. It's not tangible; this is the hitbox
 * Mario has to enter to enter BBH.
 */
static struct ObjectHitbox sBooCageHitbox = {
    /* interactType:      */ INTERACT_BBH_ENTRANCE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 120,
    /* height:            */ 300,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

/**
 * Update function for bhvBooCage.
 */
void bhv_boo_cage_loop(void) {
    obj_set_hitbox(o, &sBooCageHitbox);

    switch (o->oAction) {
        case 0:
            // Allow Mario to enter the cage once it's still on the ground.
            cur_obj_become_tangible();

            // The other useless scale
            cur_obj_scale(1.0f);

            // Set the action to BOO_CAGE_ACT_MARIO_JUMPING_IN when Mario jumps in.
            if (obj_check_if_collided_with_object(o, gMarioObject)) {
                o->oAction = BOO_CAGE_ACT_MARIO_JUMPING_IN;
            }

            break;

        case BOO_CAGE_ACT_MARIO_JUMPING_IN:
            // All this action does is wait 100 frames after Mario starts
            // jumping into the cage to set the action to BOO_CAGE_ACT_USELESS,
            // which does nothing. By extension, this action is also useless.

            if (o->oTimer > 100) {
                o->oAction = BOO_CAGE_ACT_USELESS;
            }

            break;

        case BOO_CAGE_ACT_USELESS:
            break;
    }
}
