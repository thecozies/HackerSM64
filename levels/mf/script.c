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
#include "levels/mf/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_mf_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _mf_segment_7SegmentRomStart, _mf_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _bits_skybox_mio0SegmentRomStart, _bits_skybox_mio0SegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_MF_BF, mf_bf_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MF_VINE, mf_vine_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MF_VINE2, mf_vine2_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, mf_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf0, LEVEL_CASTLE_GROUNDS, 0x01, 0x33, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf1, LEVEL_CASTLE_GROUNDS, 0x01, 0x43, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf3, LEVEL_MF, 0x01, 0xB, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 0, 3378, 280, 9385),
		OBJECT(MODEL_MF_BF, -2743, -4518, 1900, 0, -34, 0, (1 << 24), bhvMfButterfly),
		OBJECT(MODEL_MF_BF, 707, 26, -284, 0, 89, 0, (1 << 24) | (1 << 16), bhvMfButterfly),
		OBJECT(MODEL_MF_BF, 3601, 82, 201, 0, -91, 0, (2 << 24) | (2 << 16), bhvMfButterfly),
		OBJECT(MODEL_MF_BF, 2638, -112, 10067, 0, 179, 0, (0 << 24) | (3 << 16) | (1 << 8), bhvMfButterfly),
		OBJECT(MODEL_MF_BF, -1518, 369, 10513, 0, 92, 0, (2 << 24) | (4 << 16) | (1 << 8), bhvMfButterfly),
		OBJECT(MODEL_NONE, 2582, 314, 128, 0, 89, 0, (0xB << 16), bhvDeathWarp),
		OBJECT(MODEL_KOOPA_WITH_SHELL, -5597, -4543, 962, 0, 0, 0, (1 << 24) | (2 << 16), bhvKoopa),
		OBJECT(MODEL_KOOPA_FLAG, 5529, 1340, -5197, 0, 0, 0, 0x00000000, bhvKoopaFlag),
		OBJECT(MODEL_NONE, -5077, -4071, 1718, 0, 0, 0, (0xa << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_RED_COIN, 4185, 1723, -6801, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 5789, 1992, -3648, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 421, 2778, -1029, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4870, 884, 2722, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1908, -4425, -2831, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4961, -2306, -3160, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -4309, -4736, 25, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 671, 1279, -7207, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 405, 486, -3382, 0, 0, 0, (2 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_STAR, -1632, 325, 6947, 0, 92, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_STAR, 7817, 1367, 3407, 0, 92, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_STAR, -3641, 3134, -5717, 0, 92, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_STAR, 655, -2088, -5032, 0, 92, 0, (5 << 24), bhvStar),
		TERRAIN(mf_area_1_collision),
		MACRO_OBJECTS(mf_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 3378, 280, 9385),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
