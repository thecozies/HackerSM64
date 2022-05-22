#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/castle_grounds/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_castle_grounds_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _castle_grounds_segment_7SegmentRomStart, _castle_grounds_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _outside_yay0SegmentRomStart, _outside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group10_yay0SegmentRomStart, _group10_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group10_geoSegmentRomStart, _group10_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group15_yay0SegmentRomStart, _group15_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group15_geoSegmentRomStart, _group15_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _castle_grounds_segment_7SegmentRomStart, _castle_grounds_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_11), 
	JUMP_LINK(script_func_global_16), 
	LOAD_MODEL_FROM_GEO(MODEL_THI_WARP_PIPE, warp_pipe_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03, castle_grounds_geo_0006F4), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_WARP_PIPE, warp_pipe_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CASTLE_DOOR, castle_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_METAL_DOOR, metal_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_VCUTM_GRILL, castle_grounds_geo_00070C), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_FLAG, castle_grounds_geo_000660), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GROUNDS_CANNON_GRILL, castle_grounds_geo_000724), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, castle_grounds_area_1),
		WARP_NODE(0xf0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf1, LEVEL_CASTLE_GROUNDS, 0x01, 0xf1, WARP_NO_CHECKPOINT),
		WARP_NODE(0x21, LEVEL_AB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x31, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x41, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x29, LEVEL_DF, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x39, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x49, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x23, LEVEL_MF, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x33, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x43, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x25, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x35, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x45, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x55, LEVEL_BOB, 0x01, 0x0B, WARP_NO_CHECKPOINT),
		WARP_NODE(0x32, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x42, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x22, LEVEL_MTC, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 168, 872, -5037, 0, 0, 0, (0x41 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 166, 872, -5026, 0, 0, 0, (0x31 << 16), bhvAirborneStarCollectWarp),
		OBJECT(MODEL_NONE, 74, 399, -6458, 0, 0, 0, (20 << 24) | (0x21 << 16), bhvWarp),
		OBJECT(MODEL_THI_WARP_PIPE, -2166, -967, -1149, 0, 0, 0, (0x29 << 16), bhvWarpPipe),
		OBJECT(MODEL_NONE, -1531, -493, -2834, 0, -17, 0, (0x23 << 16), bhvWarp),
		OBJECT(MODEL_STICKY_PLAT, 4406, -588, 4372, 0, -180, 0, (1 << 16) | (12), bhvStickyPlat),
		OBJECT(MODEL_HANGING_PLAT, 2019, -780, 3745, 0, 0, 0, (1 << 24) | (1 << 16) | (22), bhvHangingPlat),
		OBJECT(MODEL_CASTLE_GROUNDS_METAL_DOOR, 4602, -1104, 4659, 0, -90, 0, (0x25 << 16), bhvDoorWarp),
		OBJECT(MODEL_CASTLE_GROUNDS_METAL_DOOR, 4606, -1104, 4811, 0, 90, 0, (0x55 << 16), bhvDoorWarp),
		OBJECT(MODEL_STICKY_PLAT, 4406, -169, 5121, 0, 0, 0, (1 << 16) | (12), bhvStickyPlat),
		OBJECT(MODEL_STICKY_PLAT, 4406, 314, 4372, 0, -180, 0, (1 << 16) | (12), bhvStickyPlat),
		OBJECT(MODEL_CASTLE_GROUNDS_METAL_DOOR, 3267, -1203, 176, 0, -90, 0, (10 << 24) | (0x22 << 16), bhvWarp),
		OBJECT(MODEL_NONE, -1539, -546, -995, 0, 158, 0, (0x49 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 4262, -599, 4767, 0, 90, 0, (0x45 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, 2657, -702, 129, 0, 180, 0, (0x42 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -1533, -546, -1005, 0, 158, 0, (0x39 << 16), bhvAirborneStarCollectWarp),
		OBJECT(MODEL_NONE, 4273, -599, 4769, 0, 90, 0, (0x35 << 16), bhvAirborneStarCollectWarp),
		OBJECT(MODEL_NONE, 2660, -702, 117, 0, 180, 0, (0x32 << 16), bhvAirborneStarCollectWarp),
		OBJECT(MODEL_NONE, -1224, -445, -2648, 0, 158, 0, (0x43 << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -1217, -445, -2658, 0, 158, 0, (0x33 << 16), bhvAirborneStarCollectWarp),
		OBJECT(MODEL_NONE, -24, -185, -37, 0, 0, 0, (0xf1 << 16), bhvDeathWarp),
		TERRAIN(castle_grounds_area_1_collision),
		MACRO_OBJECTS(castle_grounds_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_SPOOKY),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(1, 0, 0, 0, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
