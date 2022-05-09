extern const Trajectory ab_area_1_spline_manta_path[];
extern u8 gDoInertia;
extern u8 gDoPlatformDisplacement;

u32 aglabScratch[100];

static void manta_reset()
{
    struct Waypoint* path = segmented_to_virtual(ab_area_1_spline_manta_path);
    o->oBehParams2ndByte = 0;
    o->oPathedPrevWaypointFlags = 0;
    o->oPathedStartWaypoint = o->oPathedPrevWaypoint = path;
    o->oPosX = path->pos[0];
    o->oPosY = path->pos[1];
    o->oPosZ = path->pos[2];
}

void bhv_ab_manta_ray_init()
{
    gDoInertia = 0;
    gDoPlatformDisplacement = 0;
    cur_obj_scale(2.5f);
    manta_reset();
}

void bhv_ab_manta_ray_loop()
{
    if (0 == o->oAction)
    {
        if (gMarioObject->platform == o)
        {
            play_sound(SOUND_MARIO_TWIRL_BOUNCE, gMarioStates->marioObj->header.gfx.cameraToObject);
            drop_and_set_mario_action(gMarioStates, ACT_TWIRLING, 0);
            gMarioStates->vel[1] = 50.f;
            o->oAction = 1;
        }
    }
    else if (1 == o->oAction)
    {
        if (gMarioObject->oPosY < 1000.f)
        {
            manta_reset();
            o->oAction = 0;
            return;
        }

        int status = cur_obj_follow_path();
        if (status == PATH_REACHED_END)
        {
            o->oAction = 2;
        }
        
        if (gMarioObject->platform == o)
        {
            play_sound(SOUND_MARIO_TWIRL_BOUNCE, gMarioStates->marioObj->header.gfx.cameraToObject);
            drop_and_set_mario_action(gMarioStates, ACT_TWIRLING, 0);
            gMarioStates->vel[1] = 50.f;
        }

        o->oMantaTargetYaw   = o->oPathedTargetYaw;
        o->oMantaTargetPitch = o->oPathedTargetPitch;
        o->oForwardVel = 22.0f;

        o->oMoveAngleYaw   = approach_s16_symmetric(o->oMoveAngleYaw, o->oMantaTargetYaw, 0x80);
        o->oMoveAnglePitch = approach_s16_symmetric(o->oMoveAnglePitch, o->oMantaTargetPitch, 0x80);

        // This causes the ray to tilt as it turns.
        if ((s16) o->oMantaTargetYaw != (s16) o->oMoveAngleYaw) {
            o->oMoveAngleRoll -= 0x5B;
            if (o->oMoveAngleRoll < -DEGREES(30)) {
                o->oMoveAngleRoll = -0x4000 / 3;
            }
        } else {
            o->oMoveAngleRoll += 0x5B;
            if (o->oMoveAngleRoll > DEGREES(30)) {
                o->oMoveAngleRoll = 0x4000 / 3;
            }
        }

        cur_obj_set_pos_via_transform();
        obj_build_transform_from_pos_and_angle(o, O_POS_INDEX, O_FACE_ANGLE_INDEX);

        s16 animFrame = o->header.gfx.animInfo.animFrame;
        if (animFrame == 0) {
            cur_obj_play_sound_2(SOUND_GENERAL_MOVING_WATER);
        }
    }
    else
    {
        // -
    }
}

void bhv_ab_sand_init()
{ 
    o->oHomeY = -8000.f;
}

extern const BehaviorScript bhvHiddenStarTrigger[];
extern Vtx ab_sand_Plane_mesh_layer_5_vtx_0[25];
void bhv_ab_sand_loop()
{
    // raise self up
    if (o->oPosY < o->oHomeY)
    {
        o->oPosY += 15.f;
        if (o->oPosY > o->oHomeY)
        {
            o->oPosY = o->oHomeY;
        }
    }

    // bobble
    {
        o->oKleptoTimeUntilTargetChange++;
        f32 off = 200.f * sins(o->oKleptoTimeUntilTargetChange * 324);
        Vtx* vtx = (Vtx*) segmented_to_virtual(ab_sand_Plane_mesh_layer_5_vtx_0);
        vtx[3] .v.ob[1] = off;
        vtx[7] .v.ob[1] = off;
        vtx[12].v.ob[1] = off;
        vtx[19].v.ob[1] = off;
        vtx[24].v.ob[1] = -off;
    }

    // warping thingy
    if (0 == o->oAction)
    {
        if (gMarioStates->pos[1] < -7300.f)
        {
            spawn_star(o, 11316.f, -804.f, -8948.f);
            o->oHomeY = o->oPosY;
            o->oAction = 1;
        }
    }
    else if (1 == o->oAction)
    {
        if (gMarioStates->floorHeight == gMarioStates->pos[1])
        {
            struct Surface* floor = gMarioStates->floor;
            if (o->oHomeY < gMarioStates->pos[1] - 300.f && o->oHomeY < -1272.f && floor && (floor->type == SURFACE_NOT_SLIPPERY || floor->type == 0))
            {
                o->oKleptoStartPosX = gMarioStates->pos[0];
                o->oKleptoStartPosY = gMarioStates->pos[1];
                o->oKleptoStartPosZ = gMarioStates->pos[2];
                o->oHomeY = gMarioStates->pos[1] - 300.f;
            }
        }
        else if (gMarioStates->pos[1] < o->oPosY)
        {
            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0xc2 / 2, 0xb2 / 2, 0x30 / 2);
            o->oAction = 2;
        }
    }
    else if (2 == o->oAction)
    {
        if (o->oTimer == 12)
        {
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 3, 0xc2 / 2, 0xb2 / 2, 0x30 / 2);
            o->oAction = 1;
            gMarioStates->pos[0] = o->oKleptoStartPosX;
            gMarioStates->pos[1] = o->oKleptoStartPosY + 100.f;
            gMarioStates->pos[2] = o->oKleptoStartPosZ;
            gMarioStates->vel[0] = 0;
            gMarioStates->vel[1] = 0;
            gMarioStates->vel[2] = 0;
            gMarioStates->forwardVel = 0;
            drop_and_set_mario_action(gMarioStates, ACT_FREEFALL, 0);
        }
    }
}

static void cur_obj_find_all_objects_with_behavior_and_bparam(const BehaviorScript *behavior, struct Object** objs, int param) {
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && obj != o
            && obj->oBehParams2ndByte == param
        ) {
            *objs = obj;
            objs++;
        }

        obj = (struct Object *) obj->header.next;
    }
}

void bhv_ab_clam_ctl_init()
{
    cur_obj_find_all_objects_with_behavior_and_bparam(bhvClamShell, &o->oAbClamCtlObj0, 1);
}

void bhv_ab_clam_ctl_loop()
{
    struct Object** objs = &o->oAbClamCtlObj0;
    for (int i = 0; i < 3; i++)
    {
        struct Object* clam = objs[i];
        f32 d;
        s16 yaw;
        vec3f_get_lateral_dist_and_yaw(&o->oPosVec, &clam->oPosVec, &d, &yaw);

        clam->oMoveAngleYaw = yaw + 0x4000;
        clam->oPosX += sins(clam->oMoveAngleYaw) * 30.f;
        clam->oPosZ += coss(clam->oMoveAngleYaw) * 30.f;
    }
}

extern Gfx mat_ab_dl_tf[];
void bhv_ab_troll_loop()
{
    u8* env = (u8*) segmented_to_virtual(mat_ab_dl_tf) + 19 * 8 + 7;
    if (gMarioStates->pos[1] < 520.f || o->oDistanceToMario > 500.f)
    {
        *env = 0;
        return;
    }

    if (o->oDistanceToMario > 250.f)
    {
        *env = (500.f - o->oDistanceToMario);
    }
    else
    {
        *env = 255;
    }
}

struct MFButterflyConfig
{
    f32 speed;
    f32 top;
};

static struct MFButterflyConfig sBFCfg[] =
{
    { 1.0f, -2178.f },
    { 0.6f, 1411.f   },
    { 0.7f, 2471.f },
    { 0.7f, 900.f },
    { 1.0f, 8750.f },
};

void bhv_mf_butterfly_init()
{
    s32 bp1 = (o->oBehParams >> 24) & 0xFF;
    o->oMfButterflyVine = spawn_object(o, bp1 == 1 ? MODEL_MF_VINE : MODEL_MF_VINE2, bhvStaticObjectEx);
    o->oMfButterflyVine->oPosX = o->oPosX;
    o->oMfButterflyVine->oPosY = o->oPosY;
    o->oMfButterflyVine->oPosZ = o->oPosZ;

    if (2 == bp1)
    {
        o->oMfButterflyVine->oFaceAngleYaw += 0x4000;
        o->oMfButterflyVine->oMoveAngleYaw += 0x4000;
    }

    if (0 == bp1)
    {
        o->oMfButterflyVine->oFaceAngleYaw = 0xC000;
        o->oMfButterflyVine->oMoveAngleYaw = 0xC000;
    }
}

void bhv_mf_butterfly_loop()
{
    //print_text_fmt_int(20, 20, "X %d", (int) gMarioStates->pos[0]);
    //print_text_fmt_int(20, 40, "Y %d", (int) gMarioStates->pos[1]);
    //print_text_fmt_int(20, 60, "Z %d", (int) gMarioStates->pos[2]);

    s32 bp1 = (o->oBehParams >> 24) & 0xFF;
    s32 bp3 = (o->oBehParams >> 8)  & 0xFF;
    f32 length = 4543.f - 2178.f;
    f32* objpos = &o->oPosX;

    if (0 == o->oAction)
    {   
        if (o->oDistanceToMario < 100.f)
        {
            o->oAction = 1;
            gMarioStates->pos[1] += 10.f;
            gMarioStates->vel[1] = 10.f;
            gMarioStates->vel[bp1] = sBFCfg[o->oBehParams2ndByte].speed * 38.f;
            gMarioStates->faceAngle[1] = o->oFaceAngleYaw + 0x4000;
            cur_obj_play_sound_2(SOUND_GENERAL_SWISH_AIR_UNUSED);
            drop_and_set_mario_action(gMarioStates, ACT_FREEFALL, 0);
        }   
    }
    else
    {
        if (gMarioStates->action != ACT_FREEFALL)
        {
            o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;
            o->oAction = 0;
            return;
        }

        if (1 == bp1)
            gMarioStates->vel[bp1] = sBFCfg[o->oBehParams2ndByte].speed * (250.f - ((250 - 38) / 30) * o->oTimer);
        else
            gMarioStates->forwardVel = sBFCfg[o->oBehParams2ndByte].speed * (250.f - ((250 - 150) / 30) * o->oTimer);

        if (o->oTimer < 10)
        {
            objpos[bp1] = gMarioStates->pos[bp1];
            o->oPosY = gMarioStates->pos[1];
        }
        else
        {
            o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;
        }

        if (o->oTimer < 27)
        {
            for (int i = 0; i < 3; i++)
            {
                if (i == bp1)
                    continue;
    
                if (i != 1)
                {
                    gMarioStates->pos[i] = objpos[i];
                    gMarioStates->vel[i] = 0;
                }
                else
                {
                    // gMarioStates->pos[1] = objpos[i];
                    gMarioStates->vel[1] = 10.f;  
                }
            }
        }

        if (30 == o->oTimer)
        {
            o->oAction = 0;
        }
    }

    o->oMfButterflyVine->oPosX = o->oPosX;
    o->oMfButterflyVine->oPosY = o->oPosY;
    o->oMfButterflyVine->oPosZ = o->oPosZ;
    f32 s[3];
    s[0] = s[1] = s[2] = 1.0f;
    s[bp1 == 1 ? 1 : 2] = ((bp3 * 2 - 1) * (-1.0f)) * (sBFCfg[o->oBehParams2ndByte].top - objpos[bp1]) / (4543.f - 2178.f);
    obj_scale_xyz(o->oMfButterflyVine, s[0], s[1], s[2]);
}
