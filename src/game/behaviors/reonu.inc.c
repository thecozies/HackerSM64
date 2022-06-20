// SPRINGS

#define COLOUR_GREEN 0x00FF00
#define COLOUR_YELLOW 0xFFFF00
#define COLOUR_RED 0xFF0000

#include "src/engine/math_util.h"
#include "src/game/print.h"
#include "src/audio/external.h"
#include "src/game/spawn_sound.h"
void bhv_spring_init(void) {
    switch (BPARAM2) {
        case 0x00: // Green spring
            o->oFriction = 40.0f;
            o->oUnusedCoinParams = COLOUR_GREEN;
            break;
        case 0x01: // Yellow spring
            o->oFriction = 80.0f;
            o->oUnusedCoinParams = COLOUR_YELLOW;
            break;
        case 0x02: // Red spring
            o->oFriction = 150.0f;
            o->oUnusedCoinParams = COLOUR_RED;
            break;
    }
}


void bhv_spring_loop(void) {
    if (o->oAction == 1) {
        if (o->oTimer == 1){
            gMarioState->action = ACT_DOUBLE_JUMP;
        }
        if (o->oTimer < 4) {
            o->header.gfx.scale[1] -= 0.125f;
        }
        else if (o->oTimer < 8) {
            o->header.gfx.scale[1] += 0.125f;
        }
        else {
            o->header.gfx.scale[1] = 1;
            o->oAction = 0;
        }
    }
}

// YELLOW PLATFORMS
#define PRIM_ALPHA o->os16F6
#define BLINKING_COUNTER o->os16F4
#define PRIM_COLOUR o->oUnusedCoinParams
#define BLINKING_SPEED o->os16F8
#define BLINKING_SPEED_RED 8
#define BLINKING_SPEED_YELLOW 5
#define BLINKING_SPEED_GREEN 3

#define PLATFORM_GREEN 0x00
#define PLATFORM_YELLOW 0x01
#define PLATFORM_RED 0x02

#define X1           0x0A
#define X2           0x14
#define X3           0x1E
#define X4           0x28

enum oActionsYellowPlatform {
    YELLOW_PLATFORM_ACT_IDLE,
    YELLOW_PLATFORM_ACT_BLINKING,
    YELLOW_PLATFORM_ACT_INTANGIBLE,
};

void bhv_blinking_platform_init(void) {
    switch (BPARAM1) {
        case PLATFORM_GREEN:
            PRIM_COLOUR = COLOUR_GREEN;
            BLINKING_SPEED = BLINKING_SPEED_GREEN;
            break;
        case PLATFORM_YELLOW:
            PRIM_COLOUR = COLOUR_YELLOW;
            BLINKING_SPEED = BLINKING_SPEED_YELLOW;
            break;
        case PLATFORM_RED:
        default:
            PRIM_COLOUR = COLOUR_RED;
            BLINKING_SPEED = BLINKING_SPEED_RED;
            break;
    }

    if (BPARAM2)
        o->header.gfx.scale[0] *= BPARAM2/10;
    if (BPARAM3)
        o->header.gfx.scale[2] *= BPARAM3/10;
    if (BPARAM4)
        o->header.gfx.scale[1] *= BPARAM4/10; 

}

void blinking_platformact_idle(void) {
    PRIM_ALPHA = 180;

    cur_obj_become_tangible;
    load_object_collision_model();

    if ((gMarioObject->platform == o) || ((gMarioState->wall) && (gMarioState->wall->object == o))) {
        cur_obj_play_sound_2(SOUND_GENERAL_DOOR_TURN_KEY);
        o->oAction = YELLOW_PLATFORM_ACT_BLINKING;
    }

}

void blinking_platformact_blinking(void) {
    load_object_collision_model();
    if (BLINKING_COUNTER < 3) {
        if (PRIM_ALPHA > 80) {
            PRIM_ALPHA = approach_f32(PRIM_ALPHA, 80,BLINKING_SPEED,BLINKING_SPEED);
        } else {
            PRIM_ALPHA = 180;
            BLINKING_COUNTER++;
            if (BLINKING_COUNTER < 3) {
                cur_obj_play_sound_2(SOUND_GENERAL_DOOR_TURN_KEY);
            } else {
                cur_obj_play_sound_2(SOUND_GENERAL_WATER_LEVEL_TRIG);
            }
            
        }
    } else {
        o->oAction = YELLOW_PLATFORM_ACT_INTANGIBLE;
    }

        
}

void blinking_platformact_intangible(void) {
    cur_obj_become_intangible;

    PRIM_ALPHA = 0;
    BLINKING_COUNTER = 0;

    if (o->oTimer == 90)
        o->oAction = YELLOW_PLATFORM_ACT_IDLE;
}

ObjActionFunc sYellowPlatformActions[] = {
    blinking_platformact_idle,
    blinking_platformact_blinking,
    blinking_platformact_intangible,
};


void bhv_blinking_platform_loop(void) {
    cur_obj_call_action_function(sYellowPlatformActions);
    /*print_text_fmt_int(20,20, "ACTION %d", o->oAction);
    print_text_fmt_int(20,40, "ALPHA %d", PRIM_ALPHA);
    print_text_fmt_int(20,60, "BLINK %d", BLINKING_COUNTER);*/

}

// METEOR
#define FACE_ANGLE_SPEED o->os16F4
#define FACE_ROLL_SPEED o->os16F6

void bhv_meteor_init(void) {
    o->oFaceAngleYaw = random_u16();
    o->oFaceAngleRoll = random_u16();

    FACE_ANGLE_SPEED = (random_u16() * 15) / 65536 + 10;
    FACE_ROLL_SPEED = (random_u16() * 15) / 65536 + 10;
}

void bhv_meteor_loop(void) {
    o->oFaceAngleYaw += FACE_ANGLE_SPEED;
    o->oFaceAngleRoll += FACE_ROLL_SPEED;
}