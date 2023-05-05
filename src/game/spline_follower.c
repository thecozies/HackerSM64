#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "debug.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/geo_layout.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "helper_macros.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "memory.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "spawn_object.h"
#include "spline_follower.h"
#include "geo_misc.h"
#include "segment2.h"

void init_obj_spline(void) {
    struct Object *obj = o;
    f32 closestSplineDistSq = F32_MAX;
    Vec3f pA, pB, diff, res, closestPoint;
    u32 direction = GET_BPARAM2(obj->oBehParams);

    for (s32 i = 0; i < gCurrentArea->numSplines; i++) {
        struct Waypoint *thisWaypoint = (struct Waypoint *)gCurrentArea->splines[i];
        s32 shouldSetEnd = FALSE;

        while (thisWaypoint->flags != WAYPOINT_FLAGS_END) {
            struct Waypoint *nextWaypoint = thisWaypoint + 1;
            if (nextWaypoint->flags == WAYPOINT_FLAGS_END) {
                if (shouldSetEnd) obj->oSplineEndWaypoint = nextWaypoint;
                break;
            }

            vec3s_to_vec3f(pA, thisWaypoint->pos);
            vec3s_to_vec3f(pB, nextWaypoint->pos);
            closest_point_on_line_segment(pA, pB, &obj->oPosX, res);
            vec3f_diff(diff, &obj->oPosX, res);
            f32 distSq = vec3_sumsq(diff);
            if (distSq < closestSplineDistSq) {
                shouldSetEnd = TRUE;
                closestSplineDistSq = distSq;
                vec3f_copy(closestPoint, res);
                obj->oSplineStartWaypoint = (struct Waypoint *)gCurrentArea->splines[i];
                if (direction == SPLINE_OBJECT_MOVE_BACKWARDS) {
                    obj->oSplinePrevWaypoint = nextWaypoint;
                } else {
                    obj->oSplinePrevWaypoint = thisWaypoint;
                }
            }

            thisWaypoint++;
        }
    }

    vec3f_copy(&obj->oPosX, closestPoint);

    if (direction == SPLINE_OBJECT_MOVE_BACK_AND_FORTH) {
        o->oSplineDir = SPLINE_OBJECT_MOVE_FORWARD;
    } else if (direction == SPLINE_OBJECT_MOVE_BACK_AND_FORTH_REVERSED) {
        o->oSplineDir = SPLINE_OBJECT_MOVE_BACKWARDS;
    } else {
        o->oSplineDir = direction;
    }

    obj->oSplineActive = GET_BPARAM1(obj->oBehParams) == SPLINE_OBJECT_BHV_AUTO;
    if (!obj->oSplineActive) {
        obj->oForwardVel = 0;
    } else {
        obj->oForwardVel = (f32)GET_BPARAM3(obj->oBehParams);
    }
}

void bhv_follow_spline(void) {
    struct Object *obj = o;
 
    f32 goalSpeed = (f32)GET_BPARAM3(obj->oBehParams); 
    u32 behavior = GET_BPARAM1(obj->oBehParams);
    u32 direction = GET_BPARAM2(obj->oBehParams);

    s32 activateFromMario = behavior == SPLINE_OBJECT_BHV_MARIO_ACTIVATES;
    s32 loops = !(
        direction == SPLINE_OBJECT_MOVE_BACK_AND_FORTH
        || direction == SPLINE_OBJECT_MOVE_BACK_AND_FORTH_REVERSED
        || activateFromMario
    );

    if (!loops) {
        if (activateFromMario) {
            s32 wasActive = obj->oSplineActive;
            obj->oSplineActive = check_mario_on_object(gMarioState);
            if (wasActive != obj->oSplineActive) {
                obj->oTimer = 0;
                obj->oForwardVel = 0;
            }
            if (direction == SPLINE_OBJECT_MOVE_FORWARD) {
                obj->oSplineDir = obj->oSplineActive ? SPLINE_OBJECT_MOVE_FORWARD : SPLINE_OBJECT_MOVE_BACKWARDS;
            } else {
                obj->oSplineDir = obj->oSplineActive ? SPLINE_OBJECT_MOVE_BACKWARDS: SPLINE_OBJECT_MOVE_FORWARD;
            }
        }
    
        direction = obj->oSplineDir;
    }

    if (obj->oTimer > 10 && obj->oForwardVel < goalSpeed) {
        obj->oForwardVel += goalSpeed / 10.0f;
        obj->oForwardVel = MIN(obj->oForwardVel, goalSpeed);
    }

    struct Waypoint *thisWaypoint = obj->oSplinePrevWaypoint;
    struct Waypoint *nextWaypoint;
    if (direction == SPLINE_OBJECT_MOVE_FORWARD) {
        nextWaypoint = thisWaypoint + 1;
        if (nextWaypoint->flags == WAYPOINT_FLAGS_END) {
            if (loops) {
                nextWaypoint = obj->oSplineStartWaypoint;
            } else if (activateFromMario) {
                // clamp the waypoint to where you are
                nextWaypoint = thisWaypoint;
            } else {
                obj->oSplineDir = SPLINE_OBJECT_MOVE_BACKWARDS;
                nextWaypoint = thisWaypoint;
            }
        }
    } else {
        if (thisWaypoint == obj->oSplineStartWaypoint) {
            if (loops) {
                nextWaypoint = obj->oSplineEndWaypoint - 1;
            } else if (activateFromMario) {
                nextWaypoint = thisWaypoint;
            } else {
                obj->oSplineDir = SPLINE_OBJECT_MOVE_FORWARD;
                nextWaypoint = thisWaypoint;
            }
        } else {
            nextWaypoint = thisWaypoint - 1;
        }
    }

    Vec3f pB, dir;
    vec3s_to_vec3f(pB, nextWaypoint->pos);
    vec3f_diff(dir, pB, &obj->oPosX);
    f32 dist = vec3_sumsq(dir);
    if (dist > NEAR_ZERO) {
        dist = sqrtf(dist);
        f32 invsqrt = (1.0f / dist);
        vec3_mul_val(dir, invsqrt);
    } else {
        vec3_zero(dir);
    }

    f32 moveAmount = MIN(dist, obj->oForwardVel);
    vec3_mul_val(dir, moveAmount);
    vec3f_add(&obj->oPosX, dir);
    if (dist < obj->oForwardVel) {
        obj->oSplinePrevWaypoint = nextWaypoint;
    }
}

#ifdef RENDER_L3D_SPLINE_LINES

ALIGNED32 const Gfx sSplineLineGfx[] = {
    gsDPPipeSync(),
    gsSPClipRatio(FRUSTRATIO_2),
    gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
    gsSPClearGeometryMode(G_CULL_BACK | G_CULL_FRONT | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD),
    gsSPSetGeometryMode(G_ZBUFFER | G_FOG | G_SHADE),
    gsDPSetCombineLERP(
        0, 0, 0, PRIMITIVE,
        1, SHADE, TEXEL0, 0,
        0, 0, 0, COMBINED,
        COMBINED, 0, TEXEL0, 0
    ),
    gsDPSetAlphaDither(G_AD_NOISE),
    gsDPSetColorDither(G_CD_NOISE),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_LINE2),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPEndDisplayList(),
};

ALIGNED32 const Gfx sResetSplineLineGfx[] = {
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),

    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail( G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureFilter( G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),

    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetCycleType(G_CYC_1CYCLE),

    gsDPSetAlphaDither(G_AD_PATTERN),
    gsSPEndDisplayList(),
};

extern Mtx identityMatrixWorldScale;

void render_splines(void) {
    switch_ucode(GRAPH_NODE_UCODE_LINE);
    u8 *splineTex = segmented_to_virtual(tiny_gradient);
    gDPPipeSync(gDisplayListHead++);
    gSPMatrix(gDisplayListHead++, &identityMatrixWorldScale, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPDisplayList(gDisplayListHead++, sSplineLineGfx);

    gDPSetFogColor(gDisplayListHead++, 255, 255, 255, 255);
    gSPFogPosition(gDisplayListHead++, 980, 1000);

    // needs global fog system implemented
    // gDPSetFogColor(gDisplayListHead++, gGlobalFog.r, gGlobalFog.g, gGlobalFog.b, gGlobalFog.a);
    // gSPFogPosition(gDisplayListHead++, gGlobalFog.low, gGlobalFog.high);

    s16 sOffset = ((s16)gGlobalTimer)*1.5f;
    gDPLoadTextureBlock_4b_l(
        gDisplayListHead++,
        splineTex,
        G_IM_FMT_I,
        8, // width
        4, // height
        0,
        G_TX_NOMIRROR | G_TX_WRAP,
        G_TX_NOMIRROR | G_TX_WRAP,
        3, // mask s
        2, // mask t
        -2, // shift s
        0,  // shift t
        sOffset, // sl
        0  // tl
    );
    gDPSetTile(
        gDisplayListHead++,
        G_IM_FMT_I, G_IM_SIZ_4b,
        ((((8)>>1)+7)>>3), // line
        0, // tmem
        G_TX_RENDERTILE + 1, // tile
        0,
        (G_TX_NOMIRROR | G_TX_WRAP), 2, 0, // T settings, mask, shift
        (G_TX_NOMIRROR | G_TX_WRAP), 3, -2 // S settings, mask, shift
    );
    gDPSetTileSize(
        gDisplayListHead++,
        G_TX_RENDERTILE + 1,
        0-sOffset, 0, // s/t offset
        (8-1) << G_TEXTURE_IMAGE_FRAC,
        (4-1) << G_TEXTURE_IMAGE_FRAC
    )
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    for (int i = 0; i < gCurrentArea->numSplines; i++) {
        int vtxIndex = 0;
        int numVerts = 0;

        struct Waypoint *thisWaypoint = (struct Waypoint *)gCurrentArea->splines[i];
        // get num points
        while (thisWaypoint->flags != WAYPOINT_FLAGS_END) {
            numVerts++;
            thisWaypoint++;
        }
        thisWaypoint = (struct Waypoint *)gCurrentArea->splines[i];

        Vtx *verts = alloc_display_list(sizeof(Vtx) * numVerts);
        if (verts == NULL) return;
        while (thisWaypoint->flags != WAYPOINT_FLAGS_END) {
            make_vertex(
                verts,
                vtxIndex,
                thisWaypoint->pos[0],
                thisWaypoint->pos[1],
                thisWaypoint->pos[2],
                qs105((vtxIndex-2)*0x10), // s
                qs105(0), // t
                0, 0, 0, 255
            );

            vtxIndex++;
            thisWaypoint++;
        }

        const int bufSize = 32;

        // TODO: finish code to chunk verts to allow more than 32 segment points
        // int vertsLeft = numVerts;
        // int chunk = 0;
        // while (vertsLeft > 0) {
        //     // load verts
        //     gSPVertex(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(verts), numVerts, 0);

        //     // draw lines
        //     for (int v = 1; v < numVerts; v++) {
        //         gSPLine3D(gDisplayListHead++, v-1, v, 0);
        //     }

        //     chunk++;
        //     vertsLeft -= bufSize;
        // }

        aggress(numVerts <= bufSize, "Area spline segment has more than 32 verts");
        gSPVertex(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(verts), numVerts, 0);

        // draw lines
        for (int v = 1; v < numVerts; v++) {
            gSPLine3D(gDisplayListHead++, v-1, v, 0);
        }
    }

    gSPTexture(gDisplayListHead++, 0, 0, 0, G_TX_RENDERTILE, G_OFF);
    gDPPipeSync(gDisplayListHead++);

    switch_ucode(GRAPH_NODE_UCODE_DEFAULT);
    gDPPipeSync(gDisplayListHead++);
}

#endif // RENDER_L3D_SPLINE_LINES
