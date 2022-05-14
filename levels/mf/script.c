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
	LOAD_YAY0(0x05, _group2_yay0SegmentRomStart, _group2_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group2_geoSegmentRomStart, _group2_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_3), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_MF_BF, mf_bf_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MF_VINE, mf_vine_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MF_VINE2, mf_vine2_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MF_MILL, mf_vmill_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MF_HELP, mf_help_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_MF_PILLAR, mf_pillar_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, mf_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf0, LEVEL_CASTLE_GROUNDS, 0x01, 0x33, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf1, LEVEL_CASTLE_GROUNDS, 0x01, 0x43, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf3, LEVEL_MF, 0x01, 0xB, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_MF, 2, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0D, LEVEL_MF, 2, 0x0B, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 0, -799, 0, -2302),
		OBJECT(MODEL_MF_BF, -2743, -4518, 1900, 0, -34, 0, (1 << 24), bhvMfButterfly),
		OBJECT(MODEL_MF_BF, 707, 26, -284, 0, 89, 0, (1 << 24) | (1 << 16), bhvMfButterfly),
		OBJECT(MODEL_MF_BF, 3601, 82, 201, 0, -91, 0, (2 << 24) | (2 << 16), bhvMfButterfly),
		OBJECT(MODEL_MF_BF, 2638, -112, 10067, 0, 179, 0, (0 << 24) | (3 << 16) | (1 << 8), bhvMfButterfly),
		OBJECT(MODEL_MF_BF, -1518, 369, 10513, 0, 92, 0, (2 << 24) | (4 << 16) | (1 << 8), bhvMfButterfly),
		OBJECT(MODEL_BLUE_COIN, -5427, -4485, -2239, 0, 81, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6175, -4485, -2013, 0, 81, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6668, -4485, -1599, 0, 81, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6789, -4485, -937, 0, 81, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6602, -4485, -288, 0, 81, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -6283, -4485, 349, 0, 81, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5654, -4485, 536, 0, 81, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN_SWITCH, -4842, -4543, -2007, 0, 81, 0, 0x00000000, bhvBlueCoinSwitch),
		OBJECT(MODEL_BULLY, -1471, 0, -5570, 0, 81, 0, (0xC << 16), bhvSmallBully),
		OBJECT(MODEL_BULLY, 588, 42, -5594, 0, 81, 0, (0xC << 16), bhvSmallBully),
		OBJECT(MODEL_BULLY, 2659, 494, -6138, 0, 81, 0, (0xC << 16), bhvSmallBully),
		OBJECT(MODEL_BULLY, -2894, 386, -6690, 0, 81, 0, (0xC << 16), bhvSmallBully),
		OBJECT(MODEL_BULLY, 2793, 2037, 2976, 0, 81, 0, (0xC << 16), bhvSmallBully),
		OBJECT(MODEL_BULLY, 4024, 2589, 5120, 0, 81, 0, (0xC << 16), bhvSmallBully),
		OBJECT(MODEL_CHUCKYA, -6813, -4543, -951, 0, 81, 0, (0xC << 16), bhvChuckya),
		OBJECT(MODEL_CHUCKYA, -3334, 0, -4111, 0, 81, 0, (0xC << 16), bhvChuckya),
		OBJECT(MODEL_NONE, -3706, -4480, 1816, 0, 81, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 461, 63, -2754, 0, 81, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 4391, 494, -2642, 0, 45, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2772, 494, -5681, 0, -6, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 2728, 63, -3464, 0, 31, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, 6303, 845, -6155, 0, 43, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -2014, -2352, -2920, 0, 51, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -1708, 0, 2053, 0, 81, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -809, 1150, -7488, 0, 79, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -5731, -5200, -994, 0, 81, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -2957, -5200, 534, 0, 81, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 2582, 314, 128, 0, 89, 0, (0xB << 16), bhvDeathWarp),
		OBJECT(MODEL_NONE, -3315, -4543, -1753, 0, 81, 0, (0xC << 16), bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, -1241, 0, 1469, 0, 81, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_KOOPA_WITH_SHELL, -5918, -4543, 1505, 0, 0, 0, (1 << 24) | (2 << 16), bhvKoopa),
		OBJECT(MODEL_NONE, 5529, 1340, -5197, 0, 0, 0, 0x00000000, bhvKoopaRaceEndpoint),
		OBJECT(MODEL_KOOPA_WITHOUT_SHELL, 2494, 0, -1257, 0, 0, 0, 0x00000000, bhvKoopa),
		OBJECT(MODEL_EXCLAMATION_BOX, 605, 1732, -7187, 0, 0, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -4971, -3168, -3176, 0, 35, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 5810, 2234, -3670, 0, 0, 0, (5 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 445, 1801, -1205, 0, 0, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -1906, -4260, -2808, 0, 35, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -5708, 815, -6044, 0, 0, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_NONE, 655, -1920, -5032, 0, 92, 0, 0x00000000, bhvMfLavaCtl),
		OBJECT(MODEL_NONE, -5077, -4071, 1718, 0, 0, 0, (0xa << 16), bhvSpinAirborneWarp),
		OBJECT(MODEL_MF_MILL, -3572, 2761, -5709, 0, 170, 0, (4 << 24), bhvMfMill),
		OBJECT(MODEL_WOODEN_POST, 4212, 1605, -6833, 0, 79, 0, 0x00000000, bhvWoodenPost),
		OBJECT(MODEL_WOODEN_POST, -4868, 766, 2733, 0, 79, 0, 0x00000000, bhvWoodenPost),
		OBJECT(MODEL_WOODEN_POST, -1971, -4543, -2781, 0, 79, 0, 0x00000000, bhvWoodenPost),
		OBJECT(MODEL_WOODEN_POST, -4607, 0, -3694, 0, 79, 0, 0x00000000, bhvWoodenPost),
		OBJECT(MODEL_WOODEN_POST, 472, 2660, -1039, 0, 79, 0, 0x00000000, bhvWoodenPost),
		OBJECT(MODEL_MF_PILLAR, 464, 0, -2773, 0, 0, 0, 0x00000000, bhvMfWoodenPostMain),
		OBJECT(MODEL_STAR, -652, 27, -2786, 0, 0, 0, 0x00000000, bhvMfWoodenPostAnchor),
		OBJECT(MODEL_RED_COIN, 1972, -2411, -6672, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 3418, -2607, -3925, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -530, -2451, -7072, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 1107, -2431, -1376, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 714, -2344, -2862, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, 609, -2210, -5061, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1766, -2866, -7675, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_RED_COIN, -1474, -2515, -5791, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, -545, -2146, -4887, 0, 0, 0, (2 << 24), bhvHiddenRedCoinStar),
		OBJECT(MODEL_STAR, -1632, 325, 6947, 0, 92, 0, (3 << 24), bhvStar),
		OBJECT(MODEL_STAR, 7817, 1367, 3407, 0, 92, 0, (0 << 24), bhvStar),
		OBJECT(MODEL_STAR, -3832, 3134, -5761, 0, 92, 0, (4 << 24), bhvStar),
		OBJECT(MODEL_STAR, -677, 0, -1641, 0, 92, 0, (5 << 24), bhvHiddenStar),
		OBJECT(MODEL_NONE, -4176, 386, -5815, 0, 81, 0, (0xC << 16), bhvWarp),
		OBJECT(MODEL_NONE, -4311, 2991, -5834, 0, 81, 0, (0xD << 16), bhvWarp),
		TERRAIN(mf_area_1_collision),
		MACRO_OBJECTS(mf_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, mf_area_2),
		WARP_NODE(0x0A, LEVEL_MF, 0x01, 0x0C, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf0, LEVEL_CASTLE_GROUNDS, 0x01, 0x33, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf1, LEVEL_CASTLE_GROUNDS, 0x01, 0x43, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_MF, 0x01, 0x0D, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, -228, 0, 1950, 0, 180, 0, (0xa << 16), bhvWarp),
		OBJECT(MODEL_NONE, -212, 3555, 1861, 0, -180, 0, (0xb << 16), bhvWarp),
		TERRAIN(mf_area_2_collision),
		MACRO_OBJECTS(mf_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -799, 0, -2302),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
