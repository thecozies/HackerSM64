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


/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/ab/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_ab_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x05, _group4_yay0SegmentRomStart, _group4_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group4_geoSegmentRomStart, _group4_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _ab_segment_7SegmentRomStart, _ab_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_5), 
	LOAD_MODEL_FROM_GEO(MODEL_AB_LAVAWALL, ab_lavawall), 
	LOAD_MODEL_FROM_GEO(MODEL_AB_SAND, ab_sand), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, ab_area_1),
		WARP_NODE(0xf0, LEVEL_CASTLE_GROUNDS, 0x01, 0x31, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf1, LEVEL_CASTLE_GROUNDS, 0x41, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		INSTANT_WARP(0, 0x02, 0, 0, 0),
		MARIO_POS(0x01, -2, -6422, 1942, -12009),
		OBJECT(MODEL_BOBOMB_BUDDY, 3690, -4845, -8643, 0, 134, 0, (4 << 16), bhvBobombBuddy),
		OBJECT(MODEL_UNAGI, 424, -1462, -8381, 0, -2, 0, 0x00000000, bhvUnagi),
		OBJECT(MODEL_AB_LAVAWALL, -5608, -60, -1480, 0, -18, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -8010, -106, -1470, 0, 110, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -3203, 69, -1505, 0, -138, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -3204, 69, -1505, 0, 102, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_AB_LAVAWALL, -3206, 70, -1502, 0, -18, 0, 0x00000000, bhvAbRotatingWall),
		OBJECT(MODEL_MANTA_RAY, -6061, 1942, -11388, 0, -32, 0, 0x00000000, bhvAbManta),
		OBJECT(MODEL_NONE, -4264, 134, -4796, 0, -18, 0, (0xa << 16), bhvInstantActiveWarp),
		OBJECT(MODEL_RED_COIN, -3682, -2036, -9092, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3683, -203, -9103, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -36, -2789, -9170, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -2684, -1656, -11319, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -3877, -1642, -7513, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4022, -1004, -8534, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4887, -124, -9554, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1445, -633, -7736, 0, -2, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_AB_SAND, 4476, -8340, -8379, 0, -2, 0, 0x00000000, bhvAbSand),
		OBJECT(MODEL_SUSHI, 424, -2275, -8381, 0, -2, 0, 0x00000000, bhvSushiShark),
		OBJECT(MODEL_NONE, 438, -2585, -9138, 0, -2, 0, 0x00000000, bhvHiddenStarTrigger),
		OBJECT(MODEL_STAR, 7569, 2113, -13975, 0, -2, 0, (5 << 24), bhvStar),
		OBJECT(MODEL_NONE, -2750, 235, -4767, 0, -2, 0, (4 << 24), bhvHiddenStar),
		OBJECT(MODEL_NONE, 2015, 1153, -5608, 0, -2, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_NONE, -4247, 211, -4785, 0, -2, 0, (1 << 24), bhvHiddenRedCoinStar),
		TERRAIN(ab_area_1_collision),
		MACRO_OBJECTS(ab_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, ab_area_2),
		WARP_NODE(0xf0, LEVEL_CASTLE_GROUNDS, 0x01, 0x31, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf1, LEVEL_CASTLE_GROUNDS, 0x41, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		TERRAIN(ab_area_2_collision),
		MACRO_OBJECTS(ab_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -2, -6422, 1942, -12009),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
