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
        else if (gMarioStates->pos[1] < o->oPosY && gMarioStates->pos[0] > 1865.f)
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
    s16 yaw;
    vec3f_get_lateral_dist_and_yaw(&o->oPosVec, &o->oAbClamCtlObj0->oPosVec, &o->oAbClamCtlDistance, &yaw);
    o->oAbClamCtlDistance -= 0.f;
}

void bhv_ab_clam_ctl_loop()
{
    o->oFaceAngleYaw += 0xB9;
    struct Object** objs = &o->oAbClamCtlObj0;
    for (int i = 0; i < 6; i++)
    {
        struct Object* clam = objs[i];
        clam->oMoveAngleYaw = o->oFaceAngleYaw + 0x10000 / 6 * i;
        f32 d = o->oAbClamCtlDistance + 200.f * sins(872 * o->oTimer);
        clam->oPosX = o->oPosX + d * sins(clam->oMoveAngleYaw);
        clam->oPosZ = o->oPosZ + d * coss(clam->oMoveAngleYaw);
        clam->oPosY = find_floor_height(clam->oPosX, clam->oPosY + 100.f, clam->oPosZ);
        clam->oMoveAngleYaw += 0x4000;
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

#include "audio/load.h"
extern void set_instrument(struct SequenceChannel *seqChannel, u8 instId);
void bhv_ab_music_loop()
{
    if (o->oTimer == 0)
        return;
    
    set_instrument(gSequencePlayers[0].channels[4], 0x19);
    set_instrument(gSequencePlayers[0].channels[5], 0x19);
    set_instrument(gSequencePlayers[0].channels[6], 0x2a);
    set_instrument(gSequencePlayers[0].channels[7], 0x2a);
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
    // print_text_fmt_int(20, 20, "X %d", (int) gMarioStates->pos[0]);
    // print_text_fmt_int(20, 40, "Y %d", (int) gMarioStates->pos[1]);
    // print_text_fmt_int(20, 60, "Z %d", (int) gMarioStates->pos[2]);

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

void bhv_mf_lava_init()
{
    // -
}


extern Vtx mf_dl_mlavaline_mesh_layer_6_vtx_0[424];
void bhv_mf_lava_loop()
{
    // -2992 596-630~613 | 1104-1146~1125
    // -2664 660-702~681 | 1172-1216~1194
    // -2488 714-758~736 | 1226-1266~1246

    /*
    Y = 4.126*X - 5506
    Y = 4.197*X - 7702
      -2992 | -2664 | -2488
       613  |  681  |  736
       1125 |  1194 |  1246
     */

    if (gMarioStates->floorHeight != gMarioStates->pos[1])
        return;

    struct Surface* floor = gMarioStates->floor;
    if (!floor || floor->type != SURFACE_HARD_NOT_SLIPPERY)
        return;

    Vtx* v = segmented_to_virtual(mf_dl_mlavaline_mesh_layer_6_vtx_0);

    f32 k = (4.126f + 4.197f) / 2.f;
    f32 bl = -5506.f + 20.f;
    f32 bh = -7702.f + 80.f;
    f32 d = 10.f;

    f32 ll = k * (v->n.tc[1] - d) + bl;
    f32 lh = k * (v->n.tc[1] + d) + bl;
    f32 hl = k * (v->n.tc[1] - d) + bh;
    f32 hh = k * (v->n.tc[1] + d) + bh;
    
    int hit = 0;
    if (ll < gMarioStates->pos[1] && gMarioStates->pos[1] < lh)
        hit = 1;
        
    if (hl < gMarioStates->pos[1] && gMarioStates->pos[1] < hh)
        hit = 1;

    if (hit)
    {
        gMarioStates->hurtCounter += 8;
        drop_and_set_mario_action(gMarioStates, ACT_LAVA_BOOST, 0);
    }
}

struct ObjectHitbox sMfWoodenPostAnchorHitbox = {
    /* interactType:      */ INTERACT_GRABBABLE,
    /* downOffset:        */ 20,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 1,
    /* numLootCoins:      */ 0,
    /* radius:            */ 100,
    /* height:            */ 100,
    /* hurtboxRadius:     */ 100,
    /* hurtboxHeight:     */ 100,
};

void bhv_mf_wooden_post_anchor_init()
{
    o->oMfWoodenPostAnchorMain = cur_obj_find_nearest_object_with_behavior(bhvMfWoodenPostMain, &o->oMfWoodenPostAnchorDistance);
    obj_set_hitbox(o, &sMfWoodenPostAnchorHitbox);
}

// 464, 0, -2773
f32 gAglabThrowSpeed = 0;
void bhv_mf_wooden_post_anchor_loop()
{
    switch (o->oHeldState) {
        case HELD_FREE:
            struct Object* sparkle = spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            sparkle->oPosY += 10.f;
            o->oMfWoodenPostAnchorFixAngle = 0;
            if (gCamera->cutscene == CUTSCENE_AGLAB_WOODEN_POST_CS)
            {
                gCamera->cutscene = 0;
                reset_camera(gCamera);
            }
            break;

        case HELD_HELD:
            obj_copy_pos(o, gMarioObject);
            cur_obj_unrender_set_action_and_anim(-1, 0);

            f32 d;
            s16 yaw;
            vec3f_get_lateral_dist_and_yaw(&o->oMfWoodenPostAnchorMain->oPosVec, &o->oPosVec, &d, &yaw);
            if (0 == o->oMfWoodenPostAnchorFixAngle)
            {
                o->oMfWoodenPostAnchorFixAngle = 1;
                gMarioStates->faceAngle[1] = yaw + 0x8000;
                o->oMfWoodenPostAnchorLastMarioYaw = gMarioStates->faceAngle[1];
            }
            if (gMarioStates->action == ACT_HOLDING_BOWSER)
            {
                gMarioStates->pos[0] = o->oMfWoodenPostAnchorMain->oPosX - o->oMfWoodenPostAnchorDistance * sins(gMarioStates->faceAngle[1]);
                gMarioStates->pos[2] = o->oMfWoodenPostAnchorMain->oPosZ - o->oMfWoodenPostAnchorDistance* coss(gMarioStates->faceAngle[1]);
                s16 spd = o->oMfWoodenPostAnchorLastMarioYaw - gMarioStates->faceAngle[1];
                o->oMfWoodenPostAnchorLastMarioYaw = gMarioStates->faceAngle[1];
                f32 espd = (ABS(spd) / 20.f) - 70.f;
                gAglabThrowSpeed = 2.5f * (espd > 3.f ? espd : 3.f);
                gMarioStates->pos[1] += espd;
                gMarioStates->pos[1] = CLAMP(gMarioStates->pos[1], o->oHomeY + 136.f, o->oMfWoodenPostAnchorMain->oPosY + 200.f);
            }
            
            gCamera->cutscene = CUTSCENE_AGLAB_WOODEN_POST_CS;

            break;

        case HELD_THROWN:
            o->oPosX = gMarioStates->pos[0];
            o->oPosZ = gMarioStates->pos[2];
            o->oPosY = o->oHomeY;
            o->oHeldState = HELD_FREE;
            gCamera->cutscene = 0;
            reset_camera(gCamera);
            // cur_obj_get_thrown_or_placed(0.0f, 20.0f, 1);
            break;

        case HELD_DROPPED:
            o->oPosX = gMarioStates->pos[0];
            o->oPosZ = gMarioStates->pos[2];
            o->oPosY = o->oHomeY;
            gCamera->cutscene = 0;
            reset_camera(gCamera);
            cur_obj_get_dropped();
            break;
    }

    o->oInteractStatus = INT_STATUS_NONE;
}

void bhv_mf_wooden_post_main_init()
{
    o->oMfWoodenPostMainRope = spawn_object(o, MODEL_MF_ROPE, bhvStaticObjectEx);
    o->oMfWoodenPostMainRope->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    obj_scale_xyz(o->oMfWoodenPostMainRope, 1.2f, 1.2f, 1.2f);
    struct Object** objs = &o->oMfWoodenPostMainPosts;
    o->oPosY = -2000.f;
    cur_obj_find_all_objects_with_behavior_and_bparam(bhvWoodenPost, objs, 0);
}

void bhv_mf_wooden_post_main_loop()
{
    if (gCamera->cutscene == CUTSCENE_AGLAB_WOODEN_POST_CS)
    {
        o->oMfWoodenPostMainRope->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        o->oMfWoodenPostMainRope->oPosY = o->oPosY + 200.f;
        o->oMfWoodenPostMainRope->oFaceAngleYaw += 0x169;
    }
    else
    {
        o->oMfWoodenPostMainRope->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
    }

    if (gMarioStates->pos[1] < -800.f)
    {
        cur_obj_hide();
        o->oIntangibleTimer = -1;
    }
    else
    {
        cur_obj_unhide();
        o->oIntangibleTimer = 0;
    }

    o->oPosY = 300.f;
    int i = 0;
    for (struct Object** posts = &o->oMfWoodenPostMainPosts; *posts; posts++)
    {
        i++;
        struct Object* post = *posts;
        o->oPosY -= 1.5f * (post->oWoodenPostOffsetY);
    }
}

void mf_kq_init()
{
    o->oPosY -= 1000.f;
    o->parentObj = cur_obj_nearest_object_with_behavior(bhvKoopaRaceEndpoint);
}

void mf_kq_loop()
{
    if (o->oAction == 2)
    {
        // -
    }
    else if (o->oAction == 1)
    {
        if (o->oTimer > 100)
            o->oAction = 2;

        o->oPosY += 10.f;
    }
    else if (o->parentObj->oKoopaRaceEndpointRaceStatus)
    {
        struct Object* koopa;
        cur_obj_find_all_objects_with_behavior_and_bparam(bhvKoopa, &koopa, 2);
        o->oAction = koopa->oPosY > -10.f ? 2 : 1;
    }
}

void mf_df_level_reset_init()
{
    // -
}

static f32 sDfPositions[][3] = {
    { -862, -114, -617 },
    { -7504, 1153, -3301 },
    { 990, 1153, -3389 },
};

void mf_df_level_reset_loop()
{
    f32 d;
    struct Object* red = cur_obj_find_nearest_object_with_behavior(bhvRedCoin, &d);
    if (!red)
    {
        return;
    }

    if (0 == o->oAction)
    {
        if (0 == o->oTimer)
        {
            reset_camera(gCamera);
            set_camera_mode(gCamera, gCamera->defMode, 1);
        }

        struct Surface* floor = gMarioStates->floor;
        int type = floor ? floor->type : 0;
        int isOnCheckpoint = type == SURFACE_HARD || type == SURFACE_HARD_NOT_SLIPPERY || type == SURFACE_NOISE_DEFAULT;
        if (isOnCheckpoint)
        {
            if (floor->type == SURFACE_HARD)
                o->oDfLastCheckpoint = 0;
            if (floor->type == SURFACE_HARD_NOT_SLIPPERY)
                o->oDfLastCheckpoint = 1;
            if (floor->type == SURFACE_NOISE_DEFAULT)
                o->oDfLastCheckpoint = 2;

            o->oTimer = 0;
        }
        else
        {
            // -
        }

        int timeLeft = 10 * 30 - o->oTimer;
        if (!isOnCheckpoint && (timeLeft < 0 || (gPlayer1Controller->buttonPressed & L_TRIG) || (gMarioStates->pos[1] < -1500.f)))
        {
            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0, 0, 0);
            o->oAction = 1;
        }
        else
        {
            int f = 3 * (timeLeft % 30);
            int s = (timeLeft / 30) % 60;
            
            print_text_fmt_int(120, 20, "%02d", s);
            print_text_fmt_int(150, 20, "%02d", f);
        }
    }
    else
    {
        if (11 == o->oTimer)
        {
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 10, 0, 0, 0);
            gMarioStates->pos[0] = sDfPositions[o->oDfLastCheckpoint][0];
            gMarioStates->pos[1] = sDfPositions[o->oDfLastCheckpoint][1];
            gMarioStates->pos[2] = sDfPositions[o->oDfLastCheckpoint][2];
            gMarioStates->vel[0] = 0;
            gMarioStates->vel[1] = 0;
            gMarioStates->vel[2] = 0;
            gMarioStates->forwardVel = 0;
            drop_and_set_mario_action(gMarioStates, ACT_FREEFALL, 0);
            o->oAction = 0;
        }
    }
}

static struct Object *cur_obj_find_nearest_object_with_behavior_y_biased(const BehaviorScript *behavior) {
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;
    struct Object *closestObj = NULL;
    f32 minDist = 0x200000000;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && obj != o
        ) {
            f32 dx = o->oPosX - obj->oPosX;
            f32 dy = o->oPosY - obj->oPosY;
            f32 dz = o->oPosZ - obj->oPosZ;
            f32 objDist = dx*dx + 10*dy*dy + dz*dz;
            if (objDist < minDist) {
                closestObj = obj;
                minDist = objDist;
            }
        }

        obj = (struct Object *) obj->header.next;
    }

    return closestObj;
}

void df_arrow_loop()
{
    f32 d;
    struct Object* star = cur_obj_find_nearest_object_with_behavior(bhvHiddenRedCoinStar, &d);
    if (star)
    {
        star->oPosX = gMarioStates->pos[0];
        star->oPosY = gMarioStates->pos[1];
        star->oPosZ = gMarioStates->pos[2];
    }

    star = cur_obj_find_nearest_object_with_behavior(bhvStar, &d);
    if (star)
    {
        star->oPosX = gMarioStates->pos[0];
        star->oPosY = gMarioStates->pos[1];
        star->oPosZ = gMarioStates->pos[2];
    }

    obj_scale(o, 0.3f);
    struct Object* red = cur_obj_find_nearest_object_with_behavior_y_biased(bhvRedCoin);
    if (!red)
    {
        cur_obj_hide();
        return;
    }

    struct Surface* floor = gMarioStates->floor;
    int type = floor ? floor->type : 0;
    int isOnCheckpoint = type == SURFACE_HARD || type == SURFACE_HARD_NOT_SLIPPERY || type == SURFACE_NOISE_DEFAULT;

    if (isOnCheckpoint && (gPlayer1Controller->buttonPressed & 32))
    {
        if (obj_is_hidden(o))
        {
            cur_obj_unhide();
        }
        else
        {
            cur_obj_hide();
        }
    }
    
    o->oPosX = gMarioStates->pos[0];
    o->oPosY = gMarioStates->pos[1] + 150.f;
    o->oPosZ = gMarioStates->pos[2];

    f32 dx = o->oPosX - red->oPosX;
    f32 dy = o->oPosY - red->oPosY;
    f32 dz = o->oPosZ - red->oPosZ;
    f32 l = sqrtf(dx*dx + dz*dz);

    s16 yaw = atan2s(dz, dx) + 0x8000;
    s16 pitch = atan2s(l, dy);
    o->oFaceAngleYaw = yaw;
    o->oPosX += sins(yaw) * 80.f;
    o->oPosZ += coss(yaw) * 80.f;
    o->oFaceAnglePitch = pitch;
}
