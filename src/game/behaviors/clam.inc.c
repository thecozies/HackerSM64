// clam.inc.c

struct ObjectHitbox sClamShellHitbox = {
    /* interactType:      */ INTERACT_CLAM_OR_BUBBA,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 2,
    /* health:            */ 99,
    /* numLootCoins:      */ 0,
    /* radius:            */ 150,
    /* height:            */ 80,
    /* hurtboxRadius:     */ 150,
    /* hurtboxHeight:     */ 80,
};

void clam_act_0(void) {
    if (cur_obj_init_anim_check_frame(0, 25)) {
        cur_obj_play_sound_2(SOUND_GENERAL_CLAM_SHELL_CLOSE);
        spawn_mist_from_global();
        cur_obj_become_tangible();

        o->oClamShakeTimer = 10;
    } else if (o->oTimer > 50) {
        cur_obj_play_sound_2(SOUND_GENERAL_CLAM_SHELL_OPEN);
        o->oAction = 1;
    } else if (o->oClamShakeTimer != 0) {
        o->oClamShakeTimer--;
        cur_obj_shake_y(3.0f);
    }
}

void clam_act_1(void) {
    s16 i;
    s16 bubblesX, bubblesZ;

    if (o->oTimer > 50) {
        o->oAction = 0;
    } else if (obj_is_rendering_enabled() && cur_obj_init_anim_check_frame(1, 8)) {
        // -
    } else if (cur_obj_check_anim_frame(30)) {
        cur_obj_become_intangible();
    }
}

void bhv_clam_loop(void) {
    o->header.gfx.scale[0] = 1.5f;
    o->header.gfx.scale[1] = 2.f;
    o->header.gfx.scale[2] = 1.5f;

    switch (o->oAction) {
        case 0:
            clam_act_0();
            break;
        case 1:
            clam_act_1();
            break;
    }

    if (0 == o->oVelX)
    {
        o->oVelX = 40.f;
    }

    if (o->oBehParams2ndByte == 2)
    {
        o->oPosX += o->oVelX;
        f32 pos = find_floor_height(o->oPosX + o->oVelX * 7.f, o->oPosY + 100.f, o->oPosZ);
        if (pos < 0)
        {
            o->oVelX = -o->oVelX;
        }
        else
        {
            o->oPosY = find_floor_height(o->oPosX, o->oPosY + 100.f, o->oPosZ);
        }
    }

    obj_check_attacks(&sClamShellHitbox, o->oAction);
}
