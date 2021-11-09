#ifndef LEVEL_COMMANDS_H
#define LEVEL_COMMANDS_H

#include "command_macros_base.h"

#include "level_table.h"
#include "config.h"
#include "game/puppylights.h"

enum LevelActs {
    ACT_1 = (1 << 0),
    ACT_2 = (1 << 1),
    ACT_3 = (1 << 2),
    ACT_4 = (1 << 3),
    ACT_5 = (1 << 4),
    ACT_6 = (1 << 5),
    ALL_ACTS = (ACT_1 | ACT_2 | ACT_3 | ACT_4 | ACT_5 | ACT_6)
};

enum LevelCommandEvalOperation {
    OP_AND,
    OP_NAND,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_LEQ,
    OP_GT,
    OP_GEQ
};

enum LevelCommandGetOrSet {
    OP_SET,
    OP_GET
};

enum LevelCommandVar {
    VAR_CURR_SAVE_FILE_NUM,
    VAR_CURR_COURSE_NUM,
    VAR_CURR_ACT_NUM,
    VAR_CURR_LEVEL_NUM,
    VAR_CURR_AREA_INDEX
};

enum WarpCheckpointFlags {
    WARP_NO_CHECKPOINT = (0 << 0), // 0x00
    WARP_CHECKPOINT    = (1 << 7), // 0x80
};

enum LevelCommandCreateWhirlpoolCondition {
    WHIRLPOOL_COND_ALWAYS,
    WHIRLPOOL_COND_BOWSER2_NOT_BEATEN,
    WHIRLPOOL_COND_BOWSER2_BEATEN,
    WHIRLPOOL_COND_AT_LEAST_SECOND_STAR
};

// Head defines
enum GoddardScene {
    REGULAR_FACE = 0x2,
    DIZZY_FACE   = 0x3,
};

#ifdef NO_SEGMENTED_MEMORY
#define EXECUTE(seg, script, scriptEnd, entry) \
    CMD_BBH(0x00, 0x10, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL), \
    CMD_PTR(entry)

#define EXIT_AND_EXECUTE(seg, script, scriptEnd, entry) \
    CMD_BBH(0x01, 0x10, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL), \
    CMD_PTR(entry)
#else
#define EXECUTE(seg, script, scriptEnd, entry) \
    CMD_BBH(0x00, 0x18, seg), \
    CMD_PTR(script), \
    CMD_PTR(scriptEnd), \
    CMD_PTR(entry), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)

#define EXIT_AND_EXECUTE(seg, script, scriptEnd, entry) \
    CMD_BBH(0x01, 0x18, seg), \
    CMD_PTR(script), \
    CMD_PTR(scriptEnd), \
    CMD_PTR(entry), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)

#define EXECUTE_WITH_CODE(seg, script, scriptEnd, entry, bssStart, bssEnd) \
    CMD_BBH(0x00, 0x18, seg), \
    CMD_PTR(script), \
    CMD_PTR(scriptEnd), \
    CMD_PTR(entry), \
    CMD_PTR(bssStart), \
    CMD_PTR(bssEnd)

#define EXIT_AND_EXECUTE_WITH_CODE(seg, script, scriptEnd, entry, bssStart, bssEnd) \
    CMD_BBH(0x01, 0x18, seg), \
    CMD_PTR(script), \
    CMD_PTR(scriptEnd), \
    CMD_PTR(entry), \
    CMD_PTR(bssStart), \
    CMD_PTR(bssEnd)
#endif

#define EXIT() \
    CMD_BBH(0x02, 0x04, 0x0000)

#define SLEEP(frames) \
    CMD_BBH(0x03, 0x04, frames)

#define SLEEP_BEFORE_EXIT(frames) \
    CMD_BBH(0x04, 0x04, frames)

#define JUMP(target) \
    CMD_BBH(0x05, 0x08, 0x0000), \
    CMD_PTR(target)

#define JUMP_LINK(target) \
    CMD_BBH(0x06, 0x08, 0x0000), \
    CMD_PTR(target)

#define RETURN() \
    CMD_BBH(0x07, 0x04, 0x0000)

#define JUMP_LINK_PUSH_ARG(arg) \
    CMD_BBH(0x08, 0x04, arg)

#define JUMP_N_TIMES() \
    CMD_BBH(0x09, 0x04, 0x0000)

#define LOOP_BEGIN() \
    CMD_BBH(0x0A, 0x04, 0x0000)

#define LOOP_UNTIL(op, arg) \
    CMD_BBBB(0x0B, 0x08, op, 0x00), \
    CMD_W(arg)

#define JUMP_IF(op, arg, target) \
    CMD_BBBB(0x0C, 0x0C, op, 0x00), \
    CMD_W(arg), \
    CMD_PTR(target)

#define JUMP_LINK_IF(op, arg, target) \
    CMD_BBBB(0x0D, 0x0C, op, 0x00), \
    CMD_W(arg), \
    CMD_PTR(target)


#define SKIP_IF(op, arg) \
    CMD_BBBB(0x0E, 0x08, op, 0) \
    CMD_W(arg)

#define SKIP() \
    CMD_BBH(0x0F, 0x04, 0x0000)

#define SKIP_NOP() \
    CMD_BBH(0x10, 0x04, 0x0000)

#define CALL(arg, func) \
    CMD_BBH(0x11, 0x08, arg), \
    CMD_PTR(func)

// Calls func in a loop until it returns nonzero
#define CALL_LOOP(arg, func) \
    CMD_BBH(0x12, 0x08, arg), \
    CMD_PTR(func)

#define SET_REG(value) \
    CMD_BBH(0x13, 0x04, value)

#define PUSH_POOL() \
    CMD_BBH(0x14, 0x04, 0x0000)

#define POP_POOL() \
    CMD_BBH(0x15, 0x04, 0x0000)

#undef LOAD_MIO0
#define LOAD_MIO0(a,b,c) LOAD_YAY0(a,b,c)

#ifdef NO_SEGMENTED_MEMORY
#define FIXED_LOAD(loadAddr, romStart, romEnd) \
    CMD_BBH(0x16, 0x10, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)

#define LOAD_RAW(seg, romStart, romEnd) \
    CMD_BBH(0x17, 0x0C, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)

#define LOAD_YAY0(seg, romStart, romEnd) \
    CMD_BBH(0x18, 0x0C, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)
#else
#define FIXED_LOAD(loadAddr, romStart, romEnd) \
    CMD_BBH(0x16, 0x10, 0x0000), \
    CMD_PTR(loadAddr), \
    CMD_PTR(romStart), \
    CMD_PTR(romEnd)

#define LOAD_RAW(seg, romStart, romEnd) \
    CMD_BBH(0x17, 0x14, seg), \
    CMD_PTR(romStart), \
    CMD_PTR(romEnd), \
    CMD_PTR(0), \
    CMD_PTR(0)

#define LOAD_RAW_WITH_CODE(seg, romStart, romEnd, bssStart, bssEnd) \
    CMD_BBH(0x17, 0x14, seg), \
    CMD_PTR(romStart), \
    CMD_PTR(romEnd), \
    CMD_PTR(bssStart), \
    CMD_PTR(bssEnd)

#define LOAD_YAY0(seg, romStart, romEnd) \
    CMD_BBH(0x18, 0x0C, seg), \
    CMD_PTR(romStart), \
    CMD_PTR(romEnd)
#endif

#ifdef KEEP_MARIO_HEAD
#define LOAD_MARIO_HEAD(sethead) \
    CMD_BBH(0x19, 0x04, sethead)
#else
#define LOAD_MARIO_HEAD() \
    CMD_BBH(0x32, 0x04, 0x0000)
#endif

#ifdef NO_SEGMENTED_MEMORY
#define LOAD_YAY0_TEXTURE(seg, romStart, romEnd) \
    CMD_BBH(0x1A, 0x0C, 0x0000), \
    CMD_PTR(NULL), \
    CMD_PTR(NULL)
#else
#define LOAD_YAY0_TEXTURE(seg, romStart, romEnd) \
    CMD_BBH(0x1A, 0x0C, seg), \
    CMD_PTR(romStart), \
    CMD_PTR(romEnd)
#endif

#define CHANGE_AREA_SKYBOX(area, segStart, segEnd) \
    CMD_BBH(0x3E, 0x0C, area), \
    CMD_PTR(segStart), \
    CMD_PTR(segEnd)


#define INIT_LEVEL() \
    CMD_BBH(0x1B, 0x04, 0x0000)

#define CLEAR_LEVEL() \
    CMD_BBH(0x1C, 0x04, 0x0000)

#define ALLOC_LEVEL_POOL() \
    CMD_BBH(0x1D, 0x04, 0x0000)

#define FREE_LEVEL_POOL() \
    CMD_BBH(0x1E, 0x04, 0x0000)

#define AREA(index, geo) \
    CMD_BBBB(0x1F, 0x08, index, 0), \
    CMD_PTR(geo)

#define END_AREA() \
    CMD_BBH(0x20, 0x04, 0x0000)

#define LOAD_MODEL_FROM_DL(model, dl, layer) \
    CMD_BBH(0x21, 0x0C, 0), \
    CMD_PTR(dl), \
    CMD_HH(layer, model)

#define LOAD_MODEL_FROM_GEO(model, geo) \
    CMD_BBH(0x22, 0x08, model), \
    CMD_PTR(geo)

// unk8 is float, but doesn't really matter since CMD23 is unused
#define CMD23(model, unk4, unk8) \
    CMD_BBH(0x23, 0x08, 0), \
    CMD_PTR(unk4), \
    CMD_W(unk8)

#define OBJECT_WITH_ACTS(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh, acts) \
    CMD_BBBB(0x24, 0x1C, acts, 0x00), \
    CMD_HHHHHH(posX, posY, posZ, angleX, angleY, angleZ), \
    CMD_W(behParam), \
    CMD_PTR(beh), \
    CMD_W(model)

#define OBJECT(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh) \
    OBJECT_WITH_ACTS(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh, 0x1F)

#define MARIO(model, behArg, beh) \
    CMD_BBH(0x25, 0x0C, model), \
    CMD_W(behArg), \
    CMD_PTR(beh)

#define WARP_NODE(id, destLevel, destArea, destNode, flags) \
    CMD_BBBB(0x26, 0x08, id, destLevel), \
    CMD_BBBB(destArea, destNode, flags, 0x00)

#define PAINTING_WARP_NODE(id, destLevel, destArea, destNode, flags) \
    CMD_BBBB(0x27, 0x08, id, destLevel), \
    CMD_BBBB(destArea, destNode, flags, 0x00)

#define INSTANT_WARP(index, destArea, displaceX, displaceY, displaceZ) \
    CMD_BBBB(0x28, 0x0C, index, destArea), \
    CMD_HH(displaceX, displaceY), \
    CMD_HH(displaceZ, 0x0000)

#define LOAD_AREA(area) \
    CMD_BBBB(0x29, 0x04, area, 0x00)

#define UNLOAD_AREA(area) \
    CMD_BBBB(0x2A, 0x04, area, 0x00)

#define MARIO_POS(area, yaw, posX, posY, posZ) \
    CMD_BBBB(0x2B, 0x0C, area, 0x00), \
    CMD_HH(yaw, posX), \
    CMD_HH(posY, posZ)

// unused
#define UNLOAD_MARIO_AREA() \
    CMD_BBH(0x2C, 0x04, 0x0000)

#define UPDATE_OBJECTS() \
    CMD_BBH(0x2D, 0x04, 0x0000)

#define TERRAIN(terrainData) \
    CMD_BBH(0x2E, 0x08, 0x0000), \
    CMD_PTR(terrainData)

#define ROOMS(surfaceRooms) \
    CMD_BBH(0x2F, 0x08, 0x0000), \
    CMD_PTR(surfaceRooms)

#define SHOW_DIALOG(index, dialogId) \
    CMD_BBBB(0x30, 0x04, index, dialogId)

#define TERRAIN_TYPE(terrainType) \
    CMD_BBH(0x31, 0x04, terrainType)

#define NOP() \
    CMD_BBH(0x32, 0x04, 0x0000)

#define TRANSITION(transType, time, colorR, colorG, colorB) \
    CMD_BBBB(0x33, 0x08, transType, time), \
    CMD_BBBB(colorR, colorG, colorB, 0x00)

#define BLACKOUT(active) \
    CMD_BBBB(0x34, 0x04, active, 0x00)

#define GAMMA(enabled) \
    CMD_BBBB(0x35, 0x04, enabled, 0x00)

#define SET_BACKGROUND_MUSIC(settingsPreset, seq) \
    CMD_BBH(0x36, 0x08, settingsPreset), \
    CMD_HH(seq, 0x0000)

#define SET_MENU_MUSIC(seq) \
    CMD_BBH(0x37, 0x04, seq)

#define STOP_MUSIC(fadeOutTime) \
    CMD_BBH(0x38, 0x04, fadeOutTime)

#define MACRO_OBJECTS(objList) \
    CMD_BBH(0x39, 0x08, 0x0000), \
    CMD_PTR(objList)

// unused
#define CMD3A(unk2, unk4, unk6, unk8, unk10) \
    CMD_BBH(0x3A, 0x0C, unk2), \
    CMD_HH(unk6, unk8), \
    CMD_HH(unk10, 0x0000)

#define WHIRLPOOL(index, condition, posX, posY, posZ, strength) \
    CMD_BBBB(0x3B, 0x0C, index, condition), \
    CMD_HH(posX, posY), \
    CMD_HH(posZ, strength)

#define GET_OR_SET(op, var) \
    CMD_BBBB(0x3C, 0x04, op, var)

// Presets

#define LOAD_LEVEL_DATA(level) \
    LOAD_YAY0(/*seg*/ SEGMENT_LEVEL_DATA, /*romStart*/ _##level##_segment_7SegmentRomStart, /*romEnd*/ _##level##_segment_7SegmentRomEnd)

#define LOAD_TEXTURE_BIN(textureBin) \
    LOAD_YAY0_TEXTURE(/*seg*/ SEGMENT_TEXTURE, /*romStart*/ _##textureBin##_yay0SegmentRomStart, /*romEnd*/ _##textureBin##_yay0SegmentRomEnd)

#define LOAD_SKYBOX(skybox) \
    LOAD_YAY0(/*seg*/ SEGMENT_SKYBOX, /*romStart*/ _##skybox##_skybox_yay0SegmentRomStart, /*romEnd*/ _##skybox##_skybox_yay0SegmentRomEnd)

#define LOAD_EFFECTS() \
    LOAD_YAY0(/*seg*/ SEGMENT_EFFECT_YAY0, /*romStart*/ _effect_yay0SegmentRomStart, /*romEnd*/ _effect_yay0SegmentRomEnd)

#define LOAD_GROUPA(groupName) \
    LOAD_YAY0(/*seg*/ SEGMENT_GROUPA_YAY0, /*romStart*/ _##groupName##_yay0SegmentRomStart, /*romEnd*/ _##groupName##_yay0SegmentRomEnd), \
    LOAD_RAW( /*seg*/ SEGMENT_GROUPA_GEO,  /*romStart*/ _##groupName##_geoSegmentRomStart,  /*romEnd*/ _##groupName##_geoSegmentRomEnd)

#define LOAD_GROUPB(groupName) \
    LOAD_YAY0(/*seg*/ SEGMENT_GROUPB_YAY0, /*romStart*/ _##groupName##_yay0SegmentRomStart, /*romEnd*/ _##groupName##_yay0SegmentRomEnd), \
    LOAD_RAW (/*seg*/ SEGMENT_GROUPB_GEO,  /*romStart*/ _##groupName##_geoSegmentRomStart,  /*romEnd*/ _##groupName##_geoSegmentRomEnd)

#define LOAD_COMMON0() \
    LOAD_YAY0(/*seg*/ SEGMENT_COMMON0_YAY0, /*romStart*/ _common0_yay0SegmentRomStart, /*romEnd*/ _common0_yay0SegmentRomEnd), \
    LOAD_RAW( /*seg*/ SEGMENT_COMMON0_GEO,  /*romStart*/ _common0_geoSegmentRomStart,  /*romEnd*/ _common0_geoSegmentRomEnd)

#define LOAD_BEHAVIOR_DATA() \
    LOAD_RAW( /*seg*/ SEGMENT_BEHAVIOR_DATA, /*romStart*/ _behaviorSegmentRomStart, /*romEnd*/ _behaviorSegmentRomEnd)

#define LOAD_GODDARD() \
    FIXED_LOAD(/*loadAddr*/ _goddardSegmentStart, /*romStart*/ _goddardSegmentRomStart, /*romEnd*/ _goddardSegmentRomEnd)

#define LOAD_TITLE_SCREEN_BG() \
    LOAD_YAY0_TEXTURE(/*seg*/ SEGMENT_SKYBOX, /*romStart*/ _title_screen_bg_yay0SegmentRomStart, /*romEnd*/ _title_screen_bg_yay0SegmentRomEnd)

#define LOAD_ACTOR_MODELS(groupName) \
    JUMP_LINK(script_func_global_##groupName)

// behParams

#define BP(a, b, c, d) \
    (((a) << 24) | ((b) << 16) | ((c) << 8) | (d))

#endif // LEVEL_COMMANDS_H
