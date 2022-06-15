#include "audio/external.h"
#include "seq_ids.h"

extern void seq_player_play_sequence(u8 player, u8 seqId, u16 arg2);

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
            gMarioStates->pos[0] = o->oKleptoStartPosX;
            gMarioStates->pos[1] = o->oKleptoStartPosY + 100.f;
            gMarioStates->pos[2] = o->oKleptoStartPosZ;
            gMarioStates->vel[0] = 0;
            gMarioStates->vel[1] = 0;
            gMarioStates->vel[2] = 0;
            gMarioStates->forwardVel = 0;
            drop_and_set_mario_action(gMarioStates, ACT_FREEFALL, 0);
        }
        if (o->oTimer == 13)
        {
            reset_camera(gCamera);
        }
        if (o->oTimer == 14)
        {
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 10, 0xc2 / 2, 0xb2 / 2, 0x30 / 2);
            o->oAction = 1;
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

static struct Object* cur_obj_find_object_with_behavior_and_bparam(const BehaviorScript *behavior, int param) {
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct ObjectNode *listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    struct Object *obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr
            && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED
            && obj != o
            && obj->oBehParams2ndByte == param
        ) {
            return obj;
        }

        obj = (struct Object *) obj->header.next;
    }

    return NULL;
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
        {
            struct Object* sparkle = spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
            sparkle->oPosY += 10.f;
            o->oMfWoodenPostAnchorFixAngle = 0;
            if (gCamera->cutscene == CUTSCENE_AGLAB_WOODEN_POST_CS)
            {
                gCamera->cutscene = 0;
                reset_camera(gCamera);
            }
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

void mtc_yellow_spawner_init()
{
    o->oTimer = o->oBehParams2ndByte * 30;
    f32 d;
    o->parentObj = cur_obj_find_nearest_object_with_behavior(bhvMtcYellowPurpleSwitch, &d);
}

void mtc_yellow_spawner_loop()
{
    s32 bp1 = (o->oBehParams >> 24) & 0xFF;
    if (o->oAction == 0)
    {     
        if (bp1)
        {
            if (o->parentObj->oAction == 1)
            {
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
        if (bp1 && 0 == o->oTimer)
        {
            o->oTimer = o->oBehParams2ndByte * 30 + 1;
        }

        if (o->oTimer > 150)
        {
            o->oAction = 0;
            spawn_object(o, MODEL_MTC_BALL, bhvMtcYellowBall);
        }
    }
}

void mtc_yellow_ball_init()
{
    o->oFaceAngleYaw = random_u16();
}

void mtc_yellow_ball_loop()
{
    o->oPosY += 7.f;
    f32 scale;

    if (o->oTimer < 30)
    {
        scale = o->oTimer / 30.f;
    }
    else if (o->oTimer > 200)
    {
        scale = (230 - o->oTimer) / 30.f;
    }
    else
    {
        scale = 1.f;
    }


    f32 yscale = 1.f + 0.2f * sins(653 * o->oTimer);
    obj_scale_xyz(o, scale, yscale * scale, scale);

    if (o->oTimer == 230)
    {
        o->activeFlags = 0;
    }
}

void mtc_yellow_purple_switch_init()
{
    // -
}

void mtc_yellow_purple_switch_loop()
{
    switch (o->oAction) {
        case PURPLE_SWITCH_ACT_IDLE:
            cur_obj_set_model(MODEL_PURPLE_SWITCH);
            cur_obj_scale(1.5f);
            if (
                gMarioObject->platform == o
                && !(gMarioStates[0].action & MARIO_NO_PURPLE_SWITCH)
                && lateral_dist_between_objects(o, gMarioObject) < 127.5f
            ) {
                o->oAction = PURPLE_SWITCH_ACT_PRESSED;
            }
            break;

        case PURPLE_SWITCH_ACT_PRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 1.5f, 0.2f);
            if (o->oTimer == 3) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PURPLE_SWITCH);
                o->oAction = PURPLE_SWITCH_ACT_TICKING;
                cur_obj_shake_screen(SHAKE_POS_SMALL);
            }
            break;

        case PURPLE_SWITCH_ACT_TICKING:
            if (o->oTimer < 360) {
                //play_sound(SOUND_GENERAL2_SWITCH_TICK_FAST, gGlobalSoundSource);
            } else {
                //play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            }
            if (o->oTimer > 200) {
                o->oAction = PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF;
            }
            break;

        case PURPLE_SWITCH_ACT_UNPRESSED:
            cur_obj_scale_over_time(SCALE_AXIS_Y, 3, 0.2f, 1.5f);
            if (o->oTimer == 3) {
                o->oAction = PURPLE_SWITCH_ACT_IDLE;
            }
            break;

        case PURPLE_SWITCH_ACT_WAIT_FOR_MARIO_TO_GET_OFF:
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = PURPLE_SWITCH_ACT_UNPRESSED;
            }
            break;
    }
}

extern const Trajectory mtc_area_1_spline_greenpath[];

static void spinner_reset()
{
    struct Waypoint* path = segmented_to_virtual(mtc_area_1_spline_greenpath);
    o->oPosX = path->pos[0];
    o->oPosY = path->pos[1];
    o->oPosZ = path->pos[2];
    o->oPathedPrevWaypointFlags = 0;
    o->oPathedStartWaypoint = o->oPathedPrevWaypoint = path;
    o->oMtcGreenLineActiveStatus = 1;
}

static void spinner_line_reset()
{
    struct Object** objs = (struct Object**) aglabScratch;
    for (int i = 0; i < 9; i++)
    {
        if ((i % 2) == 0)
            continue;
        
        int lineStatus = !!((i - 1) % 4);
        obj_set_model(objs[i], (lineStatus ^ o->oMtcGreenLineActiveStatus) ? MODEL_MTC_LINE_INACTIVE : MODEL_MTC_LINE_ACTIVE);
    }
}

void mtc_green_spinner_init()
{
    o->parentObj = spawn_object(o, MODEL_MTC_PROPELLER, bhvStaticObjectEx);
    o->parentObj->oPosY -= 400.f;
    struct Waypoint* path = segmented_to_virtual(mtc_area_1_spline_greenpath);
    spinner_reset();

    struct Object** objs = (struct Object**) aglabScratch;
    static const int linePattern[] = { MODEL_MTC_LINE_WHOLE, MODEL_MTC_LINE_INACTIVE, MODEL_MTC_LINE_WHOLE, MODEL_MTC_LINE_ACTIVE };
    for (int i = 0; i < 9; i++)
    {
        struct Object* line = spawn_object(o, linePattern[i % 4], bhvStaticObjectEx);
        objs[i] = line;
        Vec3s objToNext;
        objToNext[0] = path[i + 1].pos[0] - path[i].pos[0];
        objToNext[1] = path[i + 1].pos[1] - path[i].pos[1];
        objToNext[2] = path[i + 1].pos[2] - path[i].pos[2];
        f32 len = ((f32) objToNext[0]) * ((f32) objToNext[0]) + ((f32) objToNext[1]) * ((f32) objToNext[1]) + ((f32) objToNext[2]) * ((f32) objToNext[2]);
        len = sqrtf(len);
        obj_scale_xyz(line, 1.f, 1.f, len / 900.f);
        line->oPosX = path[i].pos[0];
        line->oPosY = path[i].pos[1];
        line->oPosZ = path[i].pos[2];
        line->oFaceAngleYaw = atan2s(objToNext[2], objToNext[0]);
        line->oFaceAnglePitch = atan2s(sqrtf(sqr(objToNext[0]) + sqr(objToNext[2])), -objToNext[1]);
    }
}

void mtc_green_spinner_loop()
{
    if (o->oAction == 0)
    {
        o->oPosY = o->oHomeY + 50.f * sins(142 * o->oTimer);
        if (gMarioObject->platform == o)
        {
            o->oAction = 1;
        }
    }
    else if (o->oAction == 1)
    {
        if (gGlobalTimer % 4 == 0) {
            cur_obj_play_sound_2(SOUND_GENERAL_ELEVATOR_MOVE_2);
        }
        if (o->oPathedPrevWaypointFlags == 0) {
            o->oPathedPrevWaypoint = o->oPathedStartWaypoint;
            o->oPathedPrevWaypointFlags = WAYPOINT_FLAGS_INITIALIZED;
        }

        struct Waypoint *startWaypoint = o->oPathedStartWaypoint;
        struct Waypoint *lastWaypoint = o->oPathedPrevWaypoint;
        struct Waypoint *targetWaypoint;
        Vec3s prevToNext, objToNext;

        if ((lastWaypoint + 1)->flags != WAYPOINT_FLAGS_END) {
            targetWaypoint = lastWaypoint + 1;
        } else {
            targetWaypoint = startWaypoint;
        }

        o->oPathedPrevWaypointFlags = lastWaypoint->flags | WAYPOINT_FLAGS_INITIALIZED;

        vec3_diff(prevToNext, targetWaypoint->pos, lastWaypoint->pos);
        vec3_diff(objToNext, targetWaypoint->pos, &o->oPosVec);

        f32 len = sqrtf(objToNext[0] * objToNext[0] + objToNext[1] * objToNext[1] + objToNext[2] * objToNext[2]) / 15.f;
        if (len > 0.001f)
        {
            objToNext[0] /= len;
            objToNext[1] /= len;
            objToNext[2] /= len;
        }
        
        // If dot(prevToNext, objToNext) <= 0 (i.e. reached other side of target waypoint)
        if (vec3_dot(prevToNext, objToNext) <= 0.0f) {
            o->oPathedPrevWaypoint = targetWaypoint;
            if ((targetWaypoint + 1)->flags == WAYPOINT_FLAGS_END) {
                o->oAction = 2;
            }
        }

        if (o->oAction != 2)
        {
            int curLine = o->oPathedPrevWaypoint - o->oPathedStartWaypoint - 1;
            if ((curLine % 2 == 0))
            {
                int lineStatus = !!(curLine % 4);
                if (lineStatus ^ o->oMtcGreenLineActiveStatus)
                {
                    cur_obj_play_sound_2(SOUND_GENERAL_BIG_POUND);
                    o->oAction = 3;
                    o->oVelY = 20.f;
                }
            }
        }
        
        o->oPosX += objToNext[0];
        o->oPosY += objToNext[1];
        o->oPosZ += objToNext[2];
    }
    else if (o->oAction == 2)
    {
        // -
    }
    else if (o->oAction == 3)
    {
        print_text_centered(160, 20, "PRESS L TO RETRY");
        if (gPlayer1Controller->buttonPressed & L_TRIG)
        {
            cur_obj_become_intangible();
            o->oAction = 5;
            gMarioStates->usedObj = o;
            level_trigger_warp(gMarioStates, WARP_OP_TELEPORT);
            spinner_reset();
            spinner_line_reset();
        }

        o->oVelY -= 2.f;
        o->oPosY += o->oVelY;
        if (o->oPosY < -8000.f)
        {
            cur_obj_become_intangible();
            o->oAction = 5;
            spinner_reset();
            spinner_line_reset();
        }
    }
    else if (o->oAction == 5)
    {
        if (o->oTimer > 22)
        {
            cur_obj_become_tangible();
            o->oAction = 0;
        }
    }
    
    o->parentObj->oFaceAngleYaw += 369;
    o->parentObj->oPosX = o->oPosX;
    o->parentObj->oPosY = o->oPosY - 400.f;
    o->parentObj->oPosZ = o->oPosZ;
}

void mtc_green_line_switch_init()
{
    f32 d;
    o->parentObj = cur_obj_find_nearest_object_with_behavior(bhvMtcGreenPlatspin, &d);
}

struct SetTileSize* scroll_mtc_level_geo_mtc_line_active_get();
extern void scroll_mtc_level_geo_mtc_line_inactive_set(struct SetTileSize*);

struct SetTileSize* scroll_mtc_level_geo_mtc_line_switch_get();
void scroll_mtc_level_geo_mtc_line_switch_off_set(struct SetTileSize* ts);

void mtc_green_line_switch_loop()
{
    if (o->parentObj->oAction == 5)
    {
        obj_set_model(o, MODEL_MTC_LINE_SWITCH);
        o->oAction = 0;
        o->oFaceAngleYaw += 0x169;
        o->oPosY = o->oHomeY + 10.f * sins(242 * o->oTimer);
        return;
    }

    if (0 == o->oAction)
    {
        o->oFaceAngleYaw += 0x169;
        o->oPosY = o->oHomeY + 10.f * sins(242 * o->oTimer);
        if (o->oDistanceToMario < 150.f)
        {
            cur_obj_play_sound_2(SOUND_GENERAL_RACE_GUN_SHOT);
            obj_set_model(o, MODEL_MTC_LINE_SWITCH_OFF);
            o->oAction = 1;
            o->parentObj->oMtcGreenLineActiveStatus = !o->parentObj->oMtcGreenLineActiveStatus;      
            struct Object** objs = (struct Object**) aglabScratch;
            scroll_mtc_level_geo_mtc_line_inactive_set(scroll_mtc_level_geo_mtc_line_active_get());
            scroll_mtc_level_geo_mtc_line_switch_off_set(scroll_mtc_level_geo_mtc_line_switch_get());
            for (int i = 0; i < 9; i++)
            {
                if ((i % 2) == 0)
                    continue;
                
                int lineStatus = !!((i - 1) % 4);
                obj_set_model(objs[i], (lineStatus ^ o->parentObj->oMtcGreenLineActiveStatus) ? MODEL_MTC_LINE_INACTIVE : MODEL_MTC_LINE_ACTIVE);
            }
        }
    }
}

void mtc_blue_rotat_init()
{
    f32 d;
    o->parentObj = cur_obj_find_nearest_object_with_behavior(bhvFloorSwitchGrills, &d);
}

void mtc_blue_rotat_loop()
{
    if (0 == o->oBehParams2ndByte)
    { 
        if (0 == o->oAction)
        {
            if (o->parentObj->oAction == 1)
            {
                o->oAction = 1;
            }
            o->oMoveAnglePitch += 0x670;
        }
        else
        {
            o->oMoveAnglePitch += 0x70;
        }
    }
    else if (1 == o->oBehParams2ndByte)
    {
        o->oMoveAngleRoll += -0xB0;
    }
    else if (2 == o->oBehParams2ndByte)
    {
        o->oMoveAnglePitch += -0xD0;
    }
    else if (3 == o->oBehParams2ndByte)
    {
        o->oMoveAngleRoll += 0xB0;
    }
}

void sparkler_loop()
{
    if (gCamera->cutscene != CUTSCENE_AGLAB_MTC_CS)
        spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
}

void mtc_red_ground_init()
{

}

extern Vtx mtc_dl_Course_13_007_mesh_layer_1_vtx_0[60];
extern Vtx mtc_dl_Course_13_007_mesh_layer_1_vtx_1[12];
extern Vtx mtc_dl_Course_13_007_mesh_layer_1_vtx_2[24];
extern Vtx mtc_dl_Course_13_007_mesh_layer_1_vtx_3[14];

static void switch_vcol_alpha(Vtx* svtx, int size, u8 a)
{
    Vtx* vtx = segmented_to_virtual(svtx);
    for (int i = 0; i < size; i++)
    {
        vtx[i].v.cn[3] = a;
    }
}

#define ARGUMENT_WITH_SIZE(x) x, sizeof(x) / sizeof(*(x))

static void mtc_switch_all_vcol_alpha(u8 alpha)
{
    switch_vcol_alpha(ARGUMENT_WITH_SIZE(mtc_dl_Course_13_007_mesh_layer_1_vtx_0), alpha);
    switch_vcol_alpha(ARGUMENT_WITH_SIZE(mtc_dl_Course_13_007_mesh_layer_1_vtx_1), alpha);
    switch_vcol_alpha(ARGUMENT_WITH_SIZE(mtc_dl_Course_13_007_mesh_layer_1_vtx_2), alpha);
    switch_vcol_alpha(ARGUMENT_WITH_SIZE(mtc_dl_Course_13_007_mesh_layer_1_vtx_3), alpha);
}

extern const Collision mtc_ground_collision[];
extern const Collision mtc_ground2_collision[];
extern const Collision mtc_ground_safe_collision[];
void mtc_red_ground_loop()
{
    if (gMarioStates->pos[2] < 1600.f || gMarioStates->pos[0] > 1500.f)
    {
        if (0 != o->oAction)
        {
            o->oMtcRedStatus = 0;
            obj_set_collision_data(o, mtc_ground_collision);
            mtc_switch_all_vcol_alpha(0xff);
            o->oAction = 0;
        }
        return;
    }

    if (o->oAction == 0)
    {
        o->oAction = 1;
    }
    else
    {
        if (o->oTimer <= 200 - 0x20)
        {
            if (gPlayer1Controller->buttonPressed & L_TRIG)
            {
                o->oTimer = 200 - 0x20;
            }

            if (o->oTimer && 0 == (o->oTimer % 30))
            {
                play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            }
        }
        else
        {
            if (o->oTimer > 200 - 0x10)
                obj_set_collision_data(o, mtc_ground_safe_collision);
    
            play_sound(SOUND_GENERAL2_SWITCH_TICK_SLOW, gGlobalSoundSource);
            if (!o->oMtcRedStatus)
                mtc_switch_all_vcol_alpha((200 - o->oTimer) * 0x8);
            else
                mtc_switch_all_vcol_alpha(0xff - (200 - o->oTimer) * 0x8);
        }

        if (200 == o->oTimer)
        {
            o->oMtcRedStatus = !o->oMtcRedStatus;
            if (o->oMtcRedStatus)
            {
                obj_set_collision_data(o, mtc_ground2_collision);
                mtc_switch_all_vcol_alpha(0);
            }
            else
            {
                obj_set_collision_data(o, mtc_ground_collision);
                mtc_switch_all_vcol_alpha(0xff);
            }

            o->oTimer = 0;
        }
    }

    load_object_collision_model();
}

void mtc_brick_ctl_init()
{
    f32 d;
    o->parentObj = spawn_object(o, MODEL_STAR, bhvStar);
    o->parentObj->oBehParams = o->oBehParams;
}

static void update_home(struct Object* obj)
{
    obj->oHomeX = obj->oPosX;
    obj->oHomeY = obj->oPosY;
    obj->oHomeZ = obj->oPosZ;
}

extern s16 s8DirModeYawOffset;
void mtc_brick_ctl_loop()
{
    o->oPosX = o->parentObj->oPosX;
    o->oPosY = o->parentObj->oPosY;
    o->oPosZ = o->parentObj->oPosZ;

    if (0 == o->oAction)
    {
        if (o->oTimer > 10 && o->oDistanceToMario < 400.f)
        {
            o->oAction = 1;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            spawn_mist_particles();
            o->parentObj->oPosX = 16129.f;
            o->parentObj->oPosY = 1131.f;
            o->parentObj->oPosZ = -227.f;
        }
    }
    else if (1 == o->oAction)
    {
        if (o->oTimer > 10 && o->oDistanceToMario < 400.f)
        {
            o->oAction = 2;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            spawn_mist_particles();
            o->parentObj->oPosX = 16768.f;
            o->parentObj->oPosY = -280.f;
            o->parentObj->oPosZ = -2107.f;
        }
    }
    else if (2 == o->oAction)
    {
        if (o->oTimer > 10 && o->oDistanceToMario < 400.f)
        {
            o->oAction = 3;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            spawn_mist_particles();
            o->parentObj->oPosX = 10930.f;
            o->parentObj->oPosY = 50.f;
            o->parentObj->oPosZ = 7086.f;
        }
    }
    else if (3 == o->oAction)
    {
        if (o->oTimer > 10 && o->oDistanceToMario < 400.f)
        {
            o->oAction = 4;
            cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
            o->parentObj->oPosX = 10794.f;
            o->parentObj->oPosY = -492.f;
            o->parentObj->oPosZ = 8648.f;
            update_home(o->parentObj);
            o->oMtcGoldBrickFakeStar0 = spawn_object(o, MODEL_STAR, bhvStar);
            o->oMtcGoldBrickFakeStar0->oPosX = 10343.f;
            o->oMtcGoldBrickFakeStar0->oPosY = -335.f - 1000.f;
            o->oMtcGoldBrickFakeStar0->oPosZ = 7975.f;
            o->oMtcGoldBrickFakeStar0->oBehParams = o->parentObj->oBehParams;
            update_home(o->oMtcGoldBrickFakeStar0);
            o->oMtcGoldBrickFakeStar1 = spawn_object(o, MODEL_STAR, bhvStar);
            o->oMtcGoldBrickFakeStar1->oPosX = 11748.f;
            o->oMtcGoldBrickFakeStar1->oPosY = -591.f - 1000.f;
            o->oMtcGoldBrickFakeStar1->oPosZ = 8292.f;
            o->oMtcGoldBrickFakeStar1->oBehParams = o->parentObj->oBehParams;
            update_home(o->oMtcGoldBrickFakeStar1);
            spawn_mist_particles();
        }
    }
    else if (4 == o->oAction)
    {
        gMarioStates->pos[0] = 10933.f;
        gMarioStates->pos[1] = 10.f;
        gMarioStates->pos[2] = 7046.f;
        gCamera->cutscene = CUTSCENE_AGLAB_MTC_CS;
        if (o->oMtcGoldBrickSkillIssue)
        {
            o->oMtcGoldBrickFakeStar0->oPosY += 20.f;
            o->oMtcGoldBrickFakeStar1->oPosY += 20.f;
            if (50 == o->oTimer)
            {
                update_home(o->oMtcGoldBrickFakeStar0);
                update_home(o->oMtcGoldBrickFakeStar1);
                cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
                o->oAction = 5;
            }
        }
        else
        {
            o->oMtcGoldBrickFakeStar0->oPosY += 10.f;
            o->oMtcGoldBrickFakeStar1->oPosY += 10.f;
            if (100 == o->oTimer)
            {
                update_home(o->oMtcGoldBrickFakeStar0);
                update_home(o->oMtcGoldBrickFakeStar1);
                cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_LONG);
                o->oAction = 5;
            }
        }
    }
    else if (5 == o->oAction)
    {
        gMarioStates->pos[0] = 10933.f;
        gMarioStates->pos[1] = 10.f;
        gMarioStates->pos[2] = 7046.f;
        gCamera->cutscene = CUTSCENE_AGLAB_MTC_CS;
        int pivotTime = o->oMtcGoldBrickCount < 3 ? 30 : 10;
        if (0 == o->oTimer)
        {
            // pick 2 stars at random to swap
            int idx = random_u16() % 3;
            switch (idx)
            {
            case 0: o->oMtcGoldBrickToSwap0 = o->parentObj             ; o->oMtcGoldBrickToSwap1 = o->oMtcGoldBrickFakeStar0; break;
            case 1: o->oMtcGoldBrickToSwap0 = o->parentObj             ; o->oMtcGoldBrickToSwap1 = o->oMtcGoldBrickFakeStar1; break;
            case 2: o->oMtcGoldBrickToSwap0 = o->oMtcGoldBrickFakeStar0; o->oMtcGoldBrickToSwap1 = o->oMtcGoldBrickFakeStar1; break;
            }
        }
        else if (o->oTimer > pivotTime)
        {
            o->oTimer = 0; // it will not go oTimer==0
            update_home(o->oMtcGoldBrickToSwap0);
            update_home(o->oMtcGoldBrickToSwap1);
            o->oMtcGoldBrickCount++;
            if (o->oMtcGoldBrickCount > 10)
            {
                o->oMtcGoldBrickToSwap0 = NULL;
                o->oMtcGoldBrickToSwap1 = NULL;
                o->oMtcGoldBrickCount = 0;
                o->oAction = 6;
            }
        
            // pick 2 stars at random but not the ones that were swapped already
            struct Object* o1 = random_u16() % 2 ? o->oMtcGoldBrickToSwap0 : o->oMtcGoldBrickToSwap1;
            struct Object* o2 = NULL;
            if (o->oMtcGoldBrickToSwap0 != o->parentObj              && o->oMtcGoldBrickToSwap1 != o->parentObj)
                o2 = o->parentObj;
            if (o->oMtcGoldBrickToSwap0 != o->oMtcGoldBrickFakeStar0 && o->oMtcGoldBrickToSwap1 != o->oMtcGoldBrickFakeStar0)
                o2 = o->oMtcGoldBrickFakeStar0;
            if (o->oMtcGoldBrickToSwap0 != o->oMtcGoldBrickFakeStar1 && o->oMtcGoldBrickToSwap1 != o->oMtcGoldBrickFakeStar1)
                o2 = o->oMtcGoldBrickFakeStar1;

            o->oMtcGoldBrickToSwap0 = o1;
            o->oMtcGoldBrickToSwap1 = o2;
        }
        else
        {
            Vec3f mov;
            mov[0] = o->oMtcGoldBrickToSwap0->oHomeX - o->oMtcGoldBrickToSwap1->oHomeX;
            mov[1] = o->oMtcGoldBrickToSwap0->oHomeY - o->oMtcGoldBrickToSwap1->oHomeY;
            mov[2] = o->oMtcGoldBrickToSwap0->oHomeZ - o->oMtcGoldBrickToSwap1->oHomeZ;
            f32 scale = (float) o->oTimer / (float) pivotTime;
            mov[0] *= scale;
            mov[1] *= scale;
            mov[2] *= scale;
            o->oMtcGoldBrickToSwap0->oPosX = o->oMtcGoldBrickToSwap0->oHomeX - mov[0];
            o->oMtcGoldBrickToSwap0->oPosY = o->oMtcGoldBrickToSwap0->oHomeY - mov[1];
            o->oMtcGoldBrickToSwap0->oPosZ = o->oMtcGoldBrickToSwap0->oHomeZ - mov[2];
            
            o->oMtcGoldBrickToSwap1->oPosX = o->oMtcGoldBrickToSwap1->oHomeX + mov[0];
            o->oMtcGoldBrickToSwap1->oPosY = o->oMtcGoldBrickToSwap1->oHomeY + mov[1];
            o->oMtcGoldBrickToSwap1->oPosZ = o->oMtcGoldBrickToSwap1->oHomeZ + mov[2];
        }
    }
    else if (6 == o->oAction)
    {
        gMarioStates->pos[0] = 10933.f;
        gMarioStates->pos[1] = 10.f;
        gMarioStates->pos[2] = 7046.f;
        gCamera->cutscene = CUTSCENE_AGLAB_MTC_CS;
        if (o->oTimer > 10)
        {
            gCamera->cutscene = 0;
            reset_camera(gCamera);
            s8DirModeYawOffset = 0x8000;
            o->oAction = 7;
        }
    }
    else if (7 == o->oAction)
    {
        Vec3f dist;
        dist[0] = o->oMtcGoldBrickFakeStar0->oPosX - gMarioStates->pos[0];
        dist[1] = o->oMtcGoldBrickFakeStar0->oPosY - gMarioStates->pos[1];
        dist[2] = o->oMtcGoldBrickFakeStar0->oPosZ - gMarioStates->pos[2];
        f32 d0 = dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2];
        dist[0] = o->oMtcGoldBrickFakeStar1->oPosX - gMarioStates->pos[0];
        dist[1] = o->oMtcGoldBrickFakeStar1->oPosY - gMarioStates->pos[1];
        dist[2] = o->oMtcGoldBrickFakeStar1->oPosZ - gMarioStates->pos[2];
        f32 d1 = dist[0] * dist[0] + dist[1] * dist[1] + dist[2] * dist[2];

        if (d0 < (400.f * 400.f) || d1 < (400.f * 400.f))
        {
            play_sound(SOUND_PEACH_POWER_OF_THE_STARS, gMarioStates->marioObj->header.gfx.cameraToObject);
            o->parentObj->oPosX = 10794.f;
            o->parentObj->oPosY = -492.f;
            o->parentObj->oPosZ = 8648.f;
            update_home(o->parentObj);
            o->oMtcGoldBrickFakeStar0->oPosX = 10343.f;
            o->oMtcGoldBrickFakeStar0->oPosY = -335.f - 1000.f;
            o->oMtcGoldBrickFakeStar0->oPosZ = 7975.f;
            o->oMtcGoldBrickFakeStar0->oBehParams = o->parentObj->oBehParams;
            update_home(o->oMtcGoldBrickFakeStar0);
            o->oMtcGoldBrickFakeStar1->oPosX = 11748.f;
            o->oMtcGoldBrickFakeStar1->oPosY = -591.f - 1000.f;
            o->oMtcGoldBrickFakeStar1->oPosZ = 8292.f;
            o->oMtcGoldBrickFakeStar1->oBehParams = o->parentObj->oBehParams;
            update_home(o->oMtcGoldBrickFakeStar1);
            o->oAction = 4;
            o->oMtcGoldBrickSkillIssue = 1;
        }
    }
}

extern Vtx hf_boo_boo_mesh_layer_1_vtx_0[26];
extern Vtx hf_boo_boo_mesh_layer_1_vtx_0_backup[26];
extern Vtx hf_boo_boo_mesh_layer_1_vtx_1[7];
extern Vtx hf_boo_boo_mesh_layer_1_vtx_1_backup[7];
extern Vtx hf_boo_boo_mesh_layer_1_vtx_2[26];
extern Vtx hf_boo_boo_mesh_layer_1_vtx_2_backup[26];
extern Vtx hf_boo_boo_mesh_layer_1_vtx_3[6];
extern Vtx hf_boo_boo_mesh_layer_1_vtx_3_backup[6];

#define SIGN(x) ((x) < 0 ? -1 : 1)

static void hf_alter_boo_vtx(f32 xoff, f32 zoff, Vtx* vs, Vtx* vb, int sz)
{
    for (int i = 0; i < sz; i++)
    {
        f32 l = sqrtf(vb[i].v.ob[0] * vb[i].v.ob[0] + vb[i].v.ob[1] + vb[i].v.ob[1]) / 30.f;
        f32 zs = 1.f + sins(vb[i].v.ob[1]) / 10.f;
        vs[i].v.ob[0] = vb[i].v.ob[0] + SIGN(vb[i].v.ob[0]) * l * xoff * zs;
        vs[i].v.ob[2] = vb[i].v.ob[2] + SIGN(vb[i].v.ob[2]) * l * zoff * zs;
    }
}

void hf_boo_loop_ctl()
{
    f32 xoff = sins(0x1134 * o->oTimer);
    f32 zoff = sins(0x1027 * o->oTimer);

    {
        Vtx* vs = segmented_to_virtual(hf_boo_boo_mesh_layer_1_vtx_0);
        Vtx* vb = segmented_to_virtual(hf_boo_boo_mesh_layer_1_vtx_0_backup);
        hf_alter_boo_vtx(xoff, zoff, vs, vb, 26);
    }
    {
        Vtx* vs = segmented_to_virtual(hf_boo_boo_mesh_layer_1_vtx_1);
        Vtx* vb = segmented_to_virtual(hf_boo_boo_mesh_layer_1_vtx_1_backup);
        hf_alter_boo_vtx(xoff, zoff, vs, vb, 7);
    }
    {
        Vtx* vs = segmented_to_virtual(hf_boo_boo_mesh_layer_1_vtx_2);
        Vtx* vb = segmented_to_virtual(hf_boo_boo_mesh_layer_1_vtx_2_backup);
        hf_alter_boo_vtx(xoff, zoff, vs, vb, 26);
    }
    {
        Vtx* vs = segmented_to_virtual(hf_boo_boo_mesh_layer_1_vtx_3);
        Vtx* vb = segmented_to_virtual(hf_boo_boo_mesh_layer_1_vtx_3_backup);
        hf_alter_boo_vtx(xoff, zoff, vs, vb, 6);
    }
}

void hf_boo_init()
{
    o->oTimer = random_u16();
}

void hf_boo_loop()
{
    o->oOpacity = 100;
    obj_scale_xyz(o, 0.7f, 0.7f + 0.05 * sins(o->oTimer * 0x678), 0.7f);

    s16 realFaceAngle = o->oFaceAngleYaw + 0x4000;
    s16 dist = realFaceAngle - gMarioStates->faceAngle[1];
    s32 angleDist = ABS((s32) dist);

    if (angleDist < 0x4000)
    {
        o->oOpacity = 255;
    }
    else if (angleDist > 0x5000)
    {
        o->oOpacity = 120;
    }
    else
    {
        o->oOpacity = 120 + (0x5000 - angleDist) / 31;
    }
    if (angleDist > 0x5000)
        return;

    if (o->oPosY - 50.f > gMarioStates->pos[1])
        return;

    if (o->oDistanceToMario < 300.f)
    {
        drop_and_set_mario_action(gMarioStates, ACT_JUMP, 0);
        gMarioStates->vel[1] = 45.f;
        gMarioStates->forwardVel = 45.f;
        gMarioStates->faceAngle[1] = o->oFaceAngleYaw + 0x4000;
    }
}

void hf_goo_init()
{
    o->oTimer = random_u16();
}

void hf_goo_loop()
{
    obj_scale_xyz(o, 1.f, 1.f + 0.1 * sins(o->oTimer * 0x678), 1.f);
    if (o->oDistanceToMario < 300.f)
    {
        drop_and_set_mario_action(gMarioStates, ACT_JUMP, 0);
        gMarioStates->vel[1] = 45.f;
        gMarioStates->forwardVel = 45.f;
    }

    if (1 == o->oBehParams2ndByte)
    {
        o->oPosZ = o->oHomeZ + 300.f * sins(o->oTimer * 0x678 / 2);
    }
}

void hf_crystal_init()
{
    o->parentObj = cur_obj_find_object_with_behavior_and_bparam(bhvHfCrystal, o->oBehParams2ndByte);
}

static void hf_spawn_phase0()
{
    for (int i = 0; i < 4; i++)
    for (int j = 0; j < 3; j++)
    {
        struct Object* block = spawn_object(o, MODEL_HF_CRYSTAL_PLAT, bhvHfCrystalBlock);
        block->oFaceAngleYaw = 0;
        block->oMoveAngleYaw = 0;
        block->oPosX = (12.f/13.f) * (4500.f + 1200.f * i);
        block->oPosY = (12.f/13.f) * (500.f + 1508.f);
        block->oPosZ = (12.f/13.f) * (-4000.f + 1200.f * j);
    }

    struct Object* nc0 = spawn_object(o, MODEL_HF_CRYSTAL, bhvHfCrystal);
    nc0->oBehParams2ndByte = o->oBehParams2ndByte + 1;
    nc0->oPosX = (12.f/13.f) * (4500.f + 1200.f * 0);
    nc0->oPosY = (12.f/13.f) * (1508.f + 1150.f);
    nc0->oPosZ = (12.f/13.f) * (-4000.f + 1200.f * 0);
    nc0->oHomeX = nc0->oPosX;
    nc0->oHomeY = nc0->oPosY;
    nc0->oHomeZ = nc0->oPosZ;
    struct Object* nc1 = spawn_object(o, MODEL_HF_CRYSTAL, bhvHfCrystal);
    nc1->oBehParams2ndByte = o->oBehParams2ndByte + 1;
    nc1->oPosX = (12.f/13.f) * (4500.f + 1200.f * 4);
    nc1->oPosY = (12.f/13.f) * (1508.f + 1150.f);
    nc1->oPosZ = (12.f/13.f) * (-4000.f + 1200.f * 2);
    nc1->oHomeX = nc1->oPosX;
    nc1->oHomeY = nc1->oPosY;
    nc1->oHomeZ = nc1->oPosZ;
}

static void hf_spawn_phase1()
{
    for (int i = 4; i < 6; i++)
    for (int j = 1; j < 4; j++)
    {
        struct Object* block = spawn_object(o, MODEL_HF_CRYSTAL_PLAT, bhvHfCrystalBlock);
        block->oFaceAngleYaw = 0;
        block->oMoveAngleYaw = 0;
        block->oPosX = (12.f/13.f) * (4500.f + 1200.f * i);
        block->oPosY = (12.f/13.f) * (1000.f + 1508.f + 300.f * ((i % 2) ^ (j % 2)));
        block->oPosZ = (12.f/13.f) * (-4000.f + 1200.f * j);
    }

    struct Object* nc0 = spawn_object(o, MODEL_HF_CRYSTAL, bhvHfCrystal);
    nc0->oBehParams2ndByte = o->oBehParams2ndByte + 1;
    nc0->oPosX = (12.f/13.f) * (4500.f + 1200.f * 4);
    nc0->oPosY = (12.f/13.f) * (1508.f + 2000.f);
    nc0->oPosZ = (12.f/13.f) * (-4000.f + 1200.f * 1);
    nc0->oHomeX = nc0->oPosX;
    nc0->oHomeY = nc0->oPosY;
    nc0->oHomeZ = nc0->oPosZ;
    struct Object* nc1 = spawn_object(o, MODEL_HF_CRYSTAL, bhvHfCrystal);
    nc1->oBehParams2ndByte = o->oBehParams2ndByte + 1;
    nc1->oPosX = (12.f/13.f) * (4500.f + 1200.f * 6);
    nc1->oPosY = (12.f/13.f) * (1508.f + 2000.f);
    nc1->oPosZ = (12.f/13.f) * (-4000.f + 1200.f * 3);
    nc1->oHomeX = nc1->oPosX;
    nc1->oHomeY = nc1->oPosY;
    nc1->oHomeZ = nc1->oPosZ;
}

static void hf_spawn_phase2()
{
    for (int i = 6; i < 8; i++)
    for (int j = 2; j < 5; j++)
    {
        struct Object* block = spawn_object(o, MODEL_HF_CRYSTAL_PLAT, bhvHfCrystalBlock);
        block->oFaceAngleYaw = 0;
        block->oMoveAngleYaw = 0;
        block->oPosX = (12.f/13.f) * (4500.f + 1200.f * i);
        block->oPosY = (12.f/13.f) * (1500.f + 1508.f + 300.f * ((i % 2) + (j % 2)));
        block->oPosZ = (12.f/13.f) * (-4000.f + 1200.f * j);
    }
    
    /*
    struct Object* nc0 = spawn_object(o, MODEL_HF_CRYSTAL, bhvHfCrystal);
    nc0->oBehParams2ndByte = o->oBehParams2ndByte + 1;
    nc0->oPosX = 4500.f + 1200.f * 4;
    nc0->oPosY = 1508.f + 2100.f;
    nc0->oPosZ = -4000.f + 1200.f * 1;
    struct Object* nc1 = spawn_object(o, MODEL_HF_CRYSTAL, bhvHfCrystal);
    nc1->oBehParams2ndByte = o->oBehParams2ndByte + 1;
    nc1->oPosX = 4500.f + 1200.f * 6;
    nc1->oPosY = 1508.f + 2100.f;
    nc1->oPosZ = -4000.f + 1200.f * 4;
    */
}

void hf_crystal_loop()
{
    o->oFaceAngleYaw += 0x189;
    o->oPosY = o->oHomeY + 25.f * sins(gGlobalTimer * 343);
    if (o->oAction == 0)
    {
        if (gControllers->buttonPressed & L_TRIG)
        {
            o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;
            return;
        } 

        struct Surface* ceil = gMarioStates->ceil;
        if (!ceil || ceil->type != SURFACE_HARD_SLIPPERY)
            return;
    
        f32 d = gMarioStates->ceilHeight - gMarioStates->pos[1];
        if (d > 300.f)
            return;

        f32 dx = gMarioStates->pos[0] - o->oPosX;
        f32 dz = gMarioStates->pos[2] - o->oPosZ;
        if (ABS(dx) > 300.f || ABS(dz) > 300.f)
            return;

        o->oDfDirection = 0;
        if (dx > 80.f)
            o->oDfDirection |= 1;
        if (dz > 80.f)
            o->oDfDirection |= 2;
        if (dx < -80.f)
            o->oDfDirection |= 4;
        if (dz < -80.f)
            o->oDfDirection |= 8;

        if (o->oDfDirection)
        {
            cur_obj_play_sound_2(SOUND_GENERAL_HAUNTED_CHAIR_SWISH_AIR);
            o->oAction = 1;
        }
    }
    else if (o->oAction == 1)
    {
        if (gControllers->buttonPressed & L_TRIG)
        {
            o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;
            o->oAction = 0;
            return;
        } 

        if (o->oDfDirection & 1)
        {
            o->oPosX -= 12.f/13.f * 30.f;
        }
        if (o->oDfDirection & 2)
        {
            o->oPosZ -= 12.f/13.f *30.f;
        }
        if (o->oDfDirection & 4)
        {
            o->oPosX += 12.f/13.f *30.f;
        }
        if (o->oDfDirection & 8)
        {
            o->oPosZ += 12.f/13.f *30.f;
        }

        if (o->oTimer >= 40)
        {
            o->oDfDirection = 0;
            o->oAction = 0;
        }

        f32 parentDx = o->oPosX - o->parentObj->oPosX;
        f32 parentDz = o->oPosZ - o->parentObj->oPosZ;
        if (ABS(parentDx) < 500.f && ABS(parentDz) < 500.f)
        {
            cur_obj_play_sound_2(SOUND_GENERAL_MOVING_WATER);
            o->oAction = 2;
            o->parentObj->oAction = 2;
            if (0 == o->oBehParams2ndByte)
                hf_spawn_phase0();
            if (1 == o->oBehParams2ndByte)
                hf_spawn_phase1();
            if (2 == o->oBehParams2ndByte)
                hf_spawn_phase2();
        }
    }
    else if (o->oAction == 2)
    {
        if (o->oTimer < 30)
            obj_scale(o, 1.f - o->oTimer / 30.f);
        else
            cur_obj_become_intangible();
    }
}

void hf_crystal_block_loop()
{
    if (o->oTimer <= 30)
        obj_scale(o, o->oTimer / 30.f);
}

extern const Collision hf_ice_collision[];
extern const Collision hf_ice_collision_backup[];

extern const Vtx hf_ice_Plane_002_mesh_layer_1_vtx_0[45];
extern const Vtx hf_ice_Plane_002_mesh_layer_1_vtx_0_backup[45];

struct IceQuad
{
	/*
	 -       +
    tA - - - B
	 |       |
	bC - - - D
    */
    int tm;
    int tp;
    int bm;
    int bp;
};

static struct IceQuad sIceQuads[] = 
{
    { 18, 17, 19, 16 }, // -2
    { 21, 13, 20, 12 }, // -1
    { 23, 14, 22, 15 }, // -0

    { 1 , 0 , 6 , 7  }, // +0 
    { 2 , 3,  9 , 8  }, // +1
    { 4 , 5, 11 , 10 }, // +2
};

static void sync_coll_tri_to_visual(const s16* cb, const s16* cv, const Vtx* vb, Vtx* vv, int sz)
{
    // Need to find all instances of cb in vb and replace stuff in vv accordingly to be cv
    for (int i = 0; i < sz; i++)
    {
        if (vb[i].n.ob[0] == cb[0]
         && vb[i].n.ob[1] == cb[1]
         && vb[i].n.ob[2] == cb[2])
        {
            vv[i].n.ob[0] = cv[0];
            vv[i].n.ob[1] = cv[1];
            vv[i].n.ob[2] = cv[2];
        }
    }
}

static void lerp_quads(const s16* cb, s16* cv, const Vtx* vb, Vtx* vv, f32 t, int idx0, int idx1)
{
    for (int i = 0; i < 4; i++)
    {
        int* q0 = &sIceQuads[idx0].tm;
        int* q1 = &sIceQuads[idx1].tm;

        // alter all quads of -0 to be correct as lerp from -1 to -0
        int q0idx = q0[i];
        int q1idx = q1[i];
        const s16* q0b = &cb[3 * q0idx];
        const s16* q1b = &cb[3 * q1idx];
        s16* q1v  = &cv[2 + 3 * q1idx];
        q1v[0] = q0b[0] * t + q1b[0] * (1.f - t);
        q1v[1] = q0b[1] * t + q1b[1] * (1.f - t);
        q1v[2] = q0b[2] * t + q1b[2] * (1.f - t);
        sync_coll_tri_to_visual(q1b, q1v, vb, vv, 45);
    }
}

static void eq_quad(const s16* cb, s16* cv, const Vtx* vb, Vtx* vv, int idx0, int idx1)
{
    for (int i = 0; i < 4; i++)
    {
        int* q0 = &sIceQuads[idx0].tm;
        int* q1 = &sIceQuads[idx1].tm;
        int q0idx = q0[i];
        int q1idx = q1[i];
        const s16* q1b = &cb[3 * q1idx];
        s16* q0v  = &cv[2 + 3 * q0idx];
        s16* q1v  = &cv[2 + 3 * q1idx];
        q1v[0] = q0v[0];
        q1v[1] = q0v[1];
        q1v[2] = q0v[2];
        sync_coll_tri_to_visual(q1b, q1v, vb, vv, 45);
    }
}

void hf_ice_loop()
{
    Collision* cv = segmented_to_virtual(hf_ice_collision);
    Collision* cb = segmented_to_virtual(hf_ice_collision_backup);
    Vtx* vv = segmented_to_virtual(hf_ice_Plane_002_mesh_layer_1_vtx_0);
    Vtx* vb = segmented_to_virtual(hf_ice_Plane_002_mesh_layer_1_vtx_0_backup);

    obj_scale_xyz(o, 0.9f + 0.1f * sins(o->oTimer * 0x663), 1.f, 1.f);
    f32 t = 0.9f * sins(o->oTimer * 0x183) + 0.1f * sins(o->oTimer * 0xA63);
    if (t < 0)
    {
        lerp_quads(cb, cv, vb, vv, -t, 0 /*-2*/, 1 /*-1*/);
        eq_quad   (cb, cv, vb, vv,     1 /*-1*/, 2 /*-0*/);
        lerp_quads(cb, cv, vb, vv, -t, 5 /*+2*/, 4 /*+1*/);
        eq_quad   (cb, cv, vb, vv,     4 /*+1*/, 3 /*+0*/);
    }
    else
    {
        // all quads are active
        lerp_quads(cb, cv, vb, vv, 1.f-t, 1 /*-1*/, 2 /*-0*/);
        lerp_quads(cb, cv, vb, vv, 1.f-t, 4 /*+1*/, 3 /*+0*/);
    }
}

void hf_ice_pole_loop()
{
    obj_scale_xyz(o, 0.9f + 0.1f * sins(o->oTimer * 0x663), 0.65f + 0.4f * (0.9f * sins(o->oTimer * 0x183) + 0.1f * sins(o->oTimer * 0xA63)), 0.9f + 0.1f * sins(o->oTimer * 0x1b3));
}

void hf_ice_pole2_loop()
{
    obj_scale_xyz(o, 0.7f + 0.4f * (0.9f * sins(o->oTimer * 0x183) + 0.1f * sins(o->oTimer * 0xA63)), 1.1f + 0.1f * sins(o->oTimer * 0x1b3), 0.9f + 0.1f * sins(o->oTimer * 0x663));
}

void hf_ice_bridge_ctl()
{
    if (0 == (o->oTimer % 100))
    {
        struct Object* mover = spawn_object(o, MODEL_HF_ICE_BRIDGE, bhvHfBridgeMover);
        f32 d = o->oBehParams2ndByte ? 0.f : 80.f;
        mover->oPosZ += (o->oTimer % 200) ? -d : d;
        mover->oBehParams2ndByte = o->oBehParams2ndByte;
    }
}

void hf_ice_bridge_mover_loop()
{
    if (o->oBehParams2ndByte)
    {
        o->oMoveAngleYaw -= 369;
        o->oHomeX -= 8.f;   
    }
    else
    {
        o->oMoveAngleYaw += 169;
        o->oHomeX += 8.f;
    }

    o->oPosX = o->oHomeX;
    o->oPosY = find_floor_height(o->oHomeX, o->oPosY + 100.f, o->oHomeZ);
    if (o->oPosY < 3500.f)
    {
        o->oPosY = 5378.f;
    }

    f32 scale = 0.8f;

    if (o->oTimer <= 30)
    {
        obj_scale(o, scale * o->oTimer / 30.f);
    }

    if (o->oTimer > 370)
    {
        obj_scale(o, scale * (400 - o->oTimer) / 30.f);
    }

    if (o->oTimer >= 400)
    {
        o->activeFlags = 0;
    }
}


void hf_bridge_init()
{
    o->oDfAngleYaw = 0x4000;
    o->oDfAngleVel = 0;
}

extern Collision hf_bridge1_collision[];
extern Vtx hf_bridge1_c5_005_mesh_layer_4_vtx_0[40];
// coll 10, 11 - 21, 22
// visu 16, 19 - 33, 34

// around (-1565, 5825) & (-1959, 5842)
void hf_bridge_loop()
{
    Collision* col = segmented_to_virtual(hf_bridge1_collision);
    col += 2;
    Vtx* vtx = segmented_to_virtual(hf_bridge1_c5_005_mesh_layer_4_vtx_0);

    if (0 == o->oAction)
    {
        if (gMarioStates->pos[1] > (12.f/13.f) *5700.f && gMarioStates->pos[0] <  (12.f/13.f) * (-200.f))
        {
            play_sound(SOUND_GENERAL_OPEN_CHEST, gMarioStates->marioObj->header.gfx.cameraToObject);
            o->oAction = 1;
            o->oDfAngleVel = 40.f;
        }
    }
    else
    {
        o->oDfAngleVel += sins(o->oDfAngleYaw) * 25;
        o->oDfAngleVel += -o->oDfAngleVel * 0.04f;
        o->oDfAngleYaw += o->oDfAngleVel;
    }

    {
        f32 x = (12.f/13.f) * (-1565 + 400 * sins(o->oDfAngleYaw));
        f32 y = (12.f/13.f) * ( 5825 + 400 * coss(o->oDfAngleYaw));
        col[3 * 10     + 0] = x;
        col[3 * 10     + 1] = y;
        vtx[    16].n.ob[0] = x;
        vtx[    16].n.ob[1] = y;
        col[3 * 11     + 0] = x;
        col[3 * 11     + 1] = y;
        vtx[    19].n.ob[0] = x;
        vtx[    19].n.ob[1] = y;
    }
    {
        f32 x = (12.f/13.f) * (-778 + 400 * sins(-o->oDfAngleYaw));
        f32 y = (12.f/13.f) * (5842 + 400 * coss(-o->oDfAngleYaw));
        col[3 * 21     + 0] = x;
        col[3 * 21     + 1] = y;
        vtx[    33].n.ob[0] = x;
        vtx[    33].n.ob[1] = y;
        col[3 * 22     + 0] = x;
        col[3 * 22     + 1] = y;
        vtx[    34].n.ob[0] = x;
        vtx[    34].n.ob[1] = y;
    }
}

void hf_bridge2_init()
{

}

void hf_bridge2_loop()
{
    if (0 == o->oAction)
    {
        struct Surface* floor = gMarioStates->floor;
        if (floor && floor->type == SURFACE_HARD_NOT_SLIPPERY && gMarioStates->floorHeight == gMarioStates->pos[1])
        {
            o->oAction = 1;
        }
    }
    else
    {
        o->oFaceAnglePitch = (9000 * sins(o->oTimer * 0x183) + 1000 * sins(o->oTimer * 0xA63));
        if (gMarioStates->pos[1] < 8500.f)
        {
            o->oAction = 0;
        }
    }
}

void hf_checkpoint_loop()
{
    spawn_object(o, MODEL_NONE, bhvSparkleSpawn);
    if (o->oDistanceToMario < 150.f)
    {
        print_text_centered(160, 20, "PRESS L TO WARP BACK HERE");
    }
    if (0 == o->oAction)
    {
        if (o->oDistanceToMario < 150.f)
        {
            o->oAction = 1;
        }
    }
    else
    {
        if (gControllers->buttonPressed & L_TRIG && gMarioStates->action != 0x00880898)
        {
            gMarioStates->pos[0] = o->oPosX;
            gMarioStates->pos[1] = o->oPosY;
            gMarioStates->pos[2] = o->oPosZ;
            set_camera_mode(gCamera, CAMERA_MODE_8_DIRECTIONS, 1);
        } 
    }
}

void hf_joel_loop()
{
    obj_scale(o, 0.5f);

    if (gMarioStates->pos[2] > -4500.f)
    {
        cur_obj_hide();
    }
    else
    {
        cur_obj_unhide();
    }
    
    if (o->oBehParams2ndByte == 1)
    {
        obj_scale(o, 0.7f);
        o->oMoveAngleYaw += 0x546;
        o->oPosY = o->oHomeY - CLAMP(gMarioStates->pos[2], -5500.f, -4500.f) / 2 - 5500.f / 2;
    }
    else if (o->oBehParams2ndByte == 2)
    {
        o->oMoveAnglePitch = 0x4000;
        o->oMoveAngleYaw = 0x1200 * sins(o->oTimer * 400);
        o->oPosY = o->oHomeY - CLAMP(gMarioStates->pos[2], -5500.f, -4500.f) / 2 - 5500.f / 2;
    }
    else if (o->oBehParams2ndByte == 3)
    {
        obj_scale(o, 0.6f);
        o->oMoveAnglePitch = 0x2000;
        o->oMoveAngleYaw -= 0x146;
    }
    else if (o->oBehParams2ndByte == 4)
    {
        obj_scale_xyz(o, 0.3f, 0.8f, 3.f);
        o->oMoveAngleYaw -= 0x346;
    }
    else
    {
        o->oMoveAngleYaw += 0x346;
    }
}

extern void spawn_mist_particles_variable(s32 count, s32 offsetY, f32 size);
void hf_wind_loop()
{
    if (gMarioStates->pos[0] < 12000.f)
        return;
        
    spawn_mist_particles_variable(0, 0, 46.0f);

    struct Surface* floor = gMarioStates->floor;
    if (floor && floor->type == SURFACE_NOISE_DEFAULT)
    {
        drop_and_set_mario_action(gMarioStates, ACT_VERTICAL_WIND, 0);
        if (gMarioStates->pos[1] < 4244.f)
            gMarioStates->vel[1] = 20.f;
    }
}

// +19
extern Gfx mat_hf_scary_boo0_boom[];
extern Gfx mat_hf_scary_boo1_boom[];
extern Gfx mat_hf_scary_boo2_boom[];
extern Gfx mat_hf_scary_boo3_boom[];
extern Gfx mat_hf_scary_boo4_boom[];
extern Gfx mat_hf_scary_boo5_boom[];
extern Gfx mat_hf_scary_boo6_boom[];
extern Gfx mat_hf_scary_boo7_boom[];
extern Gfx mat_hf_scary_boo_lines_boom_layer1[]; // +14
extern Gfx mat_hf_scary_jerma_boom[]; // +12

static void set_scary_bool_alpha(u8 val)
{
    u8* a;
    a = (u8*) segmented_to_virtual(mat_hf_scary_boo0_boom) + 19*8 + 7;
    *a = val * 2;
    a = (u8*) segmented_to_virtual(mat_hf_scary_boo1_boom) + 19*8 + 7;
    *a = val * 2;
    a = (u8*) segmented_to_virtual(mat_hf_scary_boo2_boom) + 19*8 + 7;
    *a = val * 2;
    a = (u8*) segmented_to_virtual(mat_hf_scary_boo3_boom) + 19*8 + 7;
    *a = val * 2;
    a = (u8*) segmented_to_virtual(mat_hf_scary_boo4_boom) + 19*8 + 7;
    *a = val * 2;
    a = (u8*) segmented_to_virtual(mat_hf_scary_boo5_boom) + 19*8 + 7;
    *a = val * 2;
    a = (u8*) segmented_to_virtual(mat_hf_scary_boo6_boom) + 19*8 + 7;
    *a = val * 2;
    a = (u8*) segmented_to_virtual(mat_hf_scary_boo7_boom) + 19*8 + 7;
    *a = val * 2;
    a = (u8*) segmented_to_virtual(mat_hf_scary_boo_lines_boom_layer1) + 14*8 + 7;
    *a = val * 2;
    a = (u8*) segmented_to_virtual(mat_hf_scary_jerma_boom) + 12*8 + 7;
    *a = val * 4;
}

void hf_scary_boo_loop()
{
    if (0 == o->oTimer)
    {
        obj_scale(o, 0.55f);
        o->oAnimState = random_u16() % 8;
        if (0 == (random_u16() % 254))
            o->oAnimState = 8;

        o->oPosX = 12.f / 13.f * (-4120.f + 5000.f * random_float());
        o->oPosY = CLAMP(gMarioStates->pos[1], 12.f / 13.f * 1590.f, 12.f / 13.f * 11000.f) + random_f32_around_zero(2000.f) - 800.f; 
        o->oPosZ = 12.f / 13.f * (-3420.f + 6000.f * random_float());
    }

    if (o->oTimer < 30)
    {
        set_scary_bool_alpha(o->oTimer);
    }
    else if (o->oTimer < 70)
    {
        set_scary_bool_alpha(30);
    }
    else
    {
        set_scary_bool_alpha(100 - o->oTimer);
    }

    if (100 == o->oTimer)
    {
        o->oTimer = -1;
    }
}

static void set_gravity(s32 grav)
{
    if (grav == gIsGravityFlipped)
        return;

    gIsGravityFlipped = grav;
            
    if (gIsGravityFlipped)
        play_sound(SOUND_MENU_CAMERA_ZOOM_IN, gMarioObject->header.gfx.pos);
    else
        play_sound(SOUND_MENU_CAMERA_ZOOM_OUT, gMarioObject->header.gfx.pos);

    gMarioState->pos[1] = 8825.f - gMarioState->pos[1]; // Transform position. The extra 165 is due to Mario's visual model.
    if ((gMarioState->action == ACT_CRAZY_BOX_BOUNCE) || (gMarioState->action == ACT_SHOT_FROM_CANNON))
        gMarioState->pos[1] += 165.f;
    else if ((gMarioState->action == ACT_DIVE) || (gMarioState->action == ACT_FLYING))
        gMarioState->pos[1] += 65.f;

    gMarioState->vel[1] = -gMarioState->vel[1]; // Flip velocity
    gMarioState->peakHeight = 9000.f - gMarioState->peakHeight; // For fall damage
}

void vcm_ctl_loop()
{
    s32 on_floor = gMarioStates->floorHeight == gMarioStates->pos[1];
    if (!gIsGravityFlipped
      && on_floor
      && (gMarioStates->pos[0] < 4000.f || gMarioStates->pos[2] > -3000.f)
      && gMarioStates->pos[1] > -1500.f)
    {
        o->oVcmLastGoodY = gMarioStates->pos[1];
    }

    if (gMarioState->wallkickedOf == SURFACE_HARD_NOT_SLIPPERY)
    {
        set_gravity(!gIsGravityFlipped);
    }
    gMarioState->wallkickedOf = 0;

    if (0 == o->oAction)
    {
        if (!gIsGravityFlipped && gMarioStates->pos[1] < -1329.f)
        {
            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0,0,0);
            o->oAction = 1;
            return;
        }
        if (gIsGravityFlipped && gMarioStates->pos[1] < 4784.f)
        {
            play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 10, 0,0,0);
            o->oAction = 1;
            return;
        }

        u32 val4 = get_dialog_id() >= 0;
        u32 intangible = (gMarioState->action & ACT_FLAG_INTANGIBLE) != 0;
        if (!intangible
        && !val4
        && !gWarpTransition.isActive
        && sDelayedWarpOp == WARP_OP_NONE
        && on_floor
        && (gPlayer1Controller->buttonPressed & L_TRIG))  { // Flip gravity
            set_gravity(!gIsGravityFlipped);
        }
    }
    else
    {
        if (o->oTimer == 12)
        {
            set_gravity(0);
            if (gMarioStates->pos[0] < -3500.f)
            {
                // yellow
                gMarioStates->pos[0] = -3184.f;
                gMarioStates->pos[1] = 229.f;
                gMarioStates->pos[2] = 21.f;
            }
            else if (gMarioStates->pos[0] > 0.f && gMarioStates->pos[2] < -3000.f && o->oVcmLastGoodY > 2188.f)
            {
                // no A press
                gMarioStates->pos[0] = 5085.f;
                gMarioStates->pos[1] = 2636.f;
                gMarioStates->pos[2] = -2219.f;
            }
            else if (gMarioStates->pos[0] > 4000.f && gMarioStates->pos[2] > 3500.f && o->oVcmLastGoodY < 20.f)
            {
                // shoot wall jump bruh
                gMarioStates->pos[0] = 5460.f;
                gMarioStates->pos[1] = 438.f;
                gMarioStates->pos[2] = 3772.f;
            }
            else if (gMarioStates->pos[0] > 3000.f && o->oVcmLastGoodY > 2188.f)
            {
                // the top
                gMarioStates->pos[0] = 6899.f;
                gMarioStates->pos[1] = 2591.f;
                gMarioStates->pos[2] = -98.f;
            }
            else
            {
                gMarioStates->pos[0] = 0;
                gMarioStates->pos[1] = 700.f;
                gMarioStates->pos[2] = 0;
            }
            gMarioStates->vel[0] = 0;
            gMarioStates->vel[1] = 0;
            gMarioStates->vel[2] = 0;
            gMarioStates->forwardVel = 0;
            drop_and_set_mario_action(gMarioStates, ACT_FREEFALL, 0);
            reset_camera(gCamera);
        }
        if (o->oTimer == 13)
        {
            reset_camera(gCamera);
        }
        if (o->oTimer == 14)
        {
            reset_camera(gCamera);
            play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 10, 0,0,0);
            o->oAction = 0;
        }
    }
}

extern s32 gTatums;
void vcm_arrow_loop()
{
    f32 d;
    obj_scale(o, 0.3f);
    struct Object* red = cur_obj_find_nearest_object_with_behavior_y_biased(bhvRedCoin);
    if (!red)
    {
        cur_obj_hide();
        return;
    }

    // TODO:
    if (0)
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
    o->oPosY = gIsGravityFlipped ? (9000.f - gMarioStates->pos[1] - 150.f) : (gMarioStates->pos[1] + 150.f);
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

struct Pos
{
    f32 x, y, z;
};

static struct Pos gBowserPadNearPositions[] = 
{
    { 1668.f, 389.f, -1379.f }, 
    { -2025.f, 389.f, 0.f }, 
    { 1668.f, 389.f, 1113.f }, 
};

static struct Pos gBowserPadFarPositions[] = 
{
    { 6215.f, 372.f, -9607.f }, 
    { -11023.f, 389.f, -463.f }, 
    { 6600.f, 442.f, 7612.f }, 
};

extern Gfx mat_bdf_dl_bg_4_0_002[];
extern Gfx mat_bdf_dl_bg_4_0_001[];
extern Gfx mat_bdf_dl_bg_0_0[];

static Gfx* sBowserWarpCtlGfxs[] = {
    mat_bdf_dl_bg_4_0_001, 
    mat_bdf_dl_bg_0_0,
    mat_bdf_dl_bg_4_0_002, 
};

static int sBowserWarpCtlGfxOffsets[] = {
    18 * 8 + 7, 
    4 * 8 + 7, 
    18 * 8 + 7,
};

extern void bowser_course_warp_ctl_init()
{
    u8* a;
    a = (u8*) segmented_to_virtual(mat_bdf_dl_bg_4_0_002) + 18 * 8 + 7;
    *a = 0;
    a = (u8*) segmented_to_virtual(mat_bdf_dl_bg_4_0_001) + 18 * 8 + 7;
    *a = 0;
    a = (u8*) segmented_to_virtual(mat_bdf_dl_bg_0_0) + 4 * 8 + 7;
    *a = 0;
}

void bowser_course_warp_ctl_loop()
{
    if (0 == o->oAction)
    {
        struct Surface* floor = gMarioStates->floor;
        int type = floor ? floor->type : 0;
        if (SURFACE_INSTANT_WARP_1B <= type && type <= SURFACE_INSTANT_WARP_1E && gMarioStates->pos[1] == gMarioStates->floorHeight)
        {
            print_text_centered(160, 20, "PRESS L TO GO");
            if (gPlayer1Controller->buttonPressed & L_TRIG)
            {
                o->oAction = 1;
                if (type != SURFACE_INSTANT_WARP_1E)
                {
                    o->oBowserWarpCtlTarget = type - SURFACE_INSTANT_WARP_1B;
                    o->oBowserWarpCtlDirection = 0;
                }
                else
                {
                    o->oBowserWarpCtlDirection = 1;
                }
            }
        } 
    }
    else
    {
        if (o->oTimer == 1)
        {
            drop_and_set_mario_action(gMarioStates, ACT_SHOT_FROM_CANNON, 0);
        }

        if (o->oTimer > 40)
        {
            Gfx* gfx = sBowserWarpCtlGfxs[o->oBowserWarpCtlTarget];
            u8* a = (u8*) segmented_to_virtual(gfx) + sBowserWarpCtlGfxOffsets[o->oBowserWarpCtlTarget];
            if (!o->oBowserWarpCtlDirection)
            {
                *a = 15 + 8 * (o->oTimer - 40);
            }
            else
            {
                *a = 8 * (70 - o->oTimer);
            }
        }

        if (o->oTimer == 70)
            o->oAction = 0;

        struct Pos* froms = o->oBowserWarpCtlDirection ? gBowserPadFarPositions  : gBowserPadNearPositions;
        struct Pos* tos   = o->oBowserWarpCtlDirection ? gBowserPadNearPositions : gBowserPadFarPositions;

        struct Pos* from = &froms[o->oBowserWarpCtlTarget];
        struct Pos* to   = &tos  [o->oBowserWarpCtlTarget];

        f32 dx = to->x - from->x;
        f32 dy = to->y - from->y;
        f32 dz = to->z - from->z;
        
        s16 yaw = atan2s(dz, dx);
        f32 d = sqrtf(dx*dx + dz*dz);

        gMarioStates->pos[0] = from->x + dx / 70 * o->oTimer;
        gMarioStates->pos[1] = from->y + dy / 70 * o->oTimer + 2000.f * sins(o->oTimer * 0x8000 / 70);
        gMarioStates->pos[2] = from->z + dz / 70 * o->oTimer;
        gMarioStates->faceAngle[1] = yaw;
        gMarioStates->faceAngle[0] = atan2s(d, dy);
    }
}

extern const Collision bdf_p1_collision[];
extern const Collision bdf_p2_collision[];
extern const Collision bdf_p3_collision[];

static struct Pos gBowserPiecesPositions[] = 
{
    { 1467.f, 847.f, 752.f }, 
    { 1467.f, 1567.f, -93.f }, 
    { 1467.f, 2319.f, -846.f }, 
};

void bowser_pieces_init()
{
    o->parentObj = spawn_object(o, MODEL_BUBBLE, bhvStaticObjectBillboardEx);
    obj_scale(o->parentObj, 9.f);
    o->parentObj->oPosY -= 140.f;

    if (1 == o->oBehParams2ndByte)
        obj_set_collision_data(o, bdf_p1_collision);
    if (2 == o->oBehParams2ndByte)
        obj_set_collision_data(o, bdf_p2_collision);
    if (3 == o->oBehParams2ndByte)
        obj_set_collision_data(o, bdf_p3_collision);
    
    obj_scale(o, 0.2f);
    f32 d;
    o->oBowserPieceCtlKlepto = cur_obj_find_nearest_object_with_behavior(bhvKlepto, &d);
}

void bowser_pieces_loop()
{
    if (0 == o->oAction)
    {
        o->oMoveAngleYaw += 0x134;
        o->oMoveAnglePitch += 0x104;

        if (2 == o->oBehParams2ndByte)
        {
            if (o->oBowserPieceCtlKlepto->oAction == KLEPTO_ACT_STRUCK_BY_MARIO)
            {
                cur_obj_play_sound_2(SOUND_GENERAL_BUBBLES);
                o->oAction = 1;
            }

            Vec3s rotation;
            Mat4 displaceMatrix;
            rotation[0] = o->oBowserPieceCtlKlepto->oAngleVelPitch;
            rotation[1] = o->oBowserPieceCtlKlepto->oAngleVelYaw;
            rotation[2] = o->oBowserPieceCtlKlepto->oAngleVelRoll;
            Vec3f relativeOffset;
            Vec3f currentObjectOffset = { 0.f, 0.f, 0.f };
            Vec3f fromOffset = { -200.f, 0.f, 0.f };
            
            mtxf_rotate_zxy_and_translate(displaceMatrix, currentObjectOffset, rotation);
            linear_mtxf_transpose_mul_vec3f(displaceMatrix, relativeOffset, fromOffset);

            o->oPosX = o->oBowserPieceCtlKlepto->oPosX + relativeOffset[0];
            o->oPosY = o->oBowserPieceCtlKlepto->oPosY + relativeOffset[1];
            o->oPosZ = o->oBowserPieceCtlKlepto->oPosZ + relativeOffset[2];

            o->parentObj->oPosX = o->oPosX;
            o->parentObj->oPosY = o->oPosY - 140.f;
            o->parentObj->oPosZ = o->oPosZ;
        }
        else
        {
            if (o->oDistanceToMario < 120.f)
            {
                cur_obj_play_sound_2(SOUND_GENERAL_BUBBLES);
                o->oAction = 1;
            }
        }
    }
    else
    {
        if (o->oTimer <= 10)
        {
            f32 timeLeft = 10 - o->oTimer;
            obj_scale(o, timeLeft * timeLeft / 1000.f);
            obj_scale(o->parentObj, timeLeft * timeLeft * 9.f / 100.f);
        }
        else
        {
            load_object_collision_model();
        }

        if (o->oTimer == 10)
        {
            for (int i = 0; i < 10; i++)
                spawn_object(o, MODEL_WHITE_PARTICLE_SMALL, bhvSmallParticleBubbles);
    
            o->parentObj->activeFlags = 0;
            o->oMoveAngleYaw = 0;
            o->oMoveAnglePitch = 0;
            o->oPosX = gBowserPiecesPositions[o->oBehParams2ndByte - 1].x;
            o->oPosY = gBowserPiecesPositions[o->oBehParams2ndByte - 1].y;
            o->oPosZ = gBowserPiecesPositions[o->oBehParams2ndByte - 1].z;
            obj_scale(o, 1.f);
        }
    }
}

void ow_ctl_init()
{
    gDoInertia = 1;
    gDoPlatformDisplacement = 1;
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
            print_text_centered(160, 40, "GAME OVER");
            print_text_centered(160, 180, "PRESS L TO RESTART");
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

void bowser_metal_box_push_init()
{
    o->oPosY -= 20.f;
}

void bowser_metal_box_push_loop()
{
    if (0 == o->oAction)
    {
        if (-200.f  < gMarioStates->pos[2] && gMarioStates->pos[2] < 200.f
         && -1600.f < gMarioStates->pos[0] && gMarioStates->pos[0] < -1100.f
         && 1000.f  < gMarioStates->pos[1] && gMarioStates->pos[1] < 2000.f)
         {
            o->oAction = 1;
         }
    }
    else if (1 == o->oAction)
    {
        o->oPosX -= 25.f;
        if (30 == o->oTimer)
        {
            o->oAction = 2;
        }
    }
    else
    {
        o->oPosX += 10.f;
        if (75 == o->oTimer)
        {
            o->oPosX = o->oHomeX;
            o->oAction = 0;
        }
    }
}

void slide_checkpoint_init()
{

}

void slide_checkpoint_loop()
{

}
