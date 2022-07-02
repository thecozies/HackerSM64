extern u16 gDnvicUpCounter;
extern u16 gDnvicDownCounter;
extern u16 gDnvicChamber;

void ow_ctl_init()
{
    gDoInertia = 1;
    gDoPlatformDisplacement = 1;
    gDnvicUpCounter   = 0;
    gDnvicDownCounter = 0;
    gDnvicChamber     = 1;
}

void ow_ctl_loop()
{
    if (gIsGravityFlipped)
    {
        gMarioStates->health = 0x880;
        if (0 == o->oTimer)
            seq_player_play_sequence(SEQ_PLAYER_LEVEL, 0, 0);

        if (30 == o->oTimer)
            seq_player_play_sequence(SEQ_PLAYER_LEVEL, SEQ_DUCKTALES, 0);

        if (o->oTimer > 120)
        {
            print_text_centered(160, 180, "GAME OVER");
            print_text_centered(160, 60, "PRESS L TO RESTART");
            if (gPlayer1Controller->buttonPressed & L_TRIG)
            {
                gIsGravityFlipped = 0;
                o->activeFlags = 0;
            }
        }

        if (gMarioStates->pos[1] < -6000.f)
        {
            gMarioStates->pos[1] = -6000.f;
        }
    }
}

extern const Collision ow_part_brodute_collision[];
extern const Collision ow_part_arthur_collision[];
extern const Collision ow_part_gael_collision[];
extern const Collision ow_part_side_collision[];
extern const Collision ow_part_scut_collision[];

static u8 sOWIsFirstLaunchFlags = 0;
static u8 sOWIsShownFlags = 0;

extern Vec3f gAglabOWFocus;

void ow_part_init()
{
    switch(o->oBehParams2ndByte)
    {
        case 1:
        obj_set_collision_data(o, ow_part_brodute_collision);
        break;
        case 2:
        obj_set_collision_data(o, ow_part_arthur_collision);
        break;
        case 3:
        obj_set_collision_data(o, ow_part_gael_collision);
        break;
        case 4:
        obj_set_collision_data(o, ow_part_side_collision);
        break;
        case 5:
        obj_set_collision_data(o, ow_part_scut_collision);
        break;
    }

    s32 active = 0;
    switch (o->oBehParams2ndByte)
    {
        case 1:
        {
            u8 starFlags = save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(COURSE_AB));
            active = 0 != starFlags;
        }
        break;
        case 2:
        {
            u8 starFlags = save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(COURSE_MTC));
            active = 0 != starFlags;
        }
        break;
        case 3:
        {
            u8 starFlags = save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(COURSE_MF));
            active = 0 != starFlags;
        }
        break;
        case 4:
        {
            u8 starFlags = save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(COURSE_HF));
            active = 0 != starFlags;
        }
        break;
        case 5:
        {
            u8 agtStars   = save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(COURSE_TOTWC));
            u8 reonuStars = save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(COURSE_SA));
            u8 axoStars   = save_file_get_star_flags((gCurrSaveFileNum - 1), COURSE_NUM_TO_INDEX(COURSE_COTMC));
            active = agtStars || reonuStars || axoStars;
        }
        break;
    }

    if (!active)
    {
        o->activeFlags = 0;
    }
    
    u8 flag = 1 << o->oBehParams2ndByte;
    if (sOWIsFirstLaunchFlags & flag)
    {
        if (active)
        {
            if (!(sOWIsShownFlags & flag))
            {
                gCamera->cutscene = CUTSCENE_AGLAB_OW_CS;
                o->oOWPartShowCutscene = 1;
            }
            sOWIsShownFlags |= flag;
        }
    }
    else
    {
        sOWIsFirstLaunchFlags |= flag;
        if (active)
            sOWIsShownFlags |= flag;
    }

    o->oHomeX = gMarioStates->pos[0];
    o->oHomeY = gMarioStates->pos[1];
    o->oHomeZ = gMarioStates->pos[2];

    if (1 == o->oOWPartShowCutscene)
    {
        gAglabOWFocus[0] = o->oPosX;
        gAglabOWFocus[1] = o->oPosY;
        gAglabOWFocus[2] = o->oPosZ;
    }
}

static void fixMario()
{
    gMarioStates->pos[0] = o->oHomeX;
    gMarioStates->pos[1] = o->oHomeY;
    gMarioStates->pos[2] = o->oHomeZ;
}

void ow_part_loop()
{
    if (0 == o->oAction)
    {
        if (1 == o->oOWPartShowCutscene)
        {
            fixMario();
            if (o->oTimer < 100)
            {
                gCamera->cutscene = CUTSCENE_AGLAB_OW_CS;
            }
            if (300 == o->oTimer)
            {
                gCamera->cutscene = 0;
                reset_camera(gCamera);
                o->oAction = 1;
            }            
        }
        else
        {
            o->oAction = 1;
        }
    }
    else
    {
        if (o->collisionData)
            load_object_collision_model();
    }
}
