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
#include "levels/hf/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_hf_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _hf_segment_7SegmentRomStart, _hf_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x05, _group1_yay0SegmentRomStart, _group1_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group1_geoSegmentRomStart, _group1_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_2), 
	LOAD_MODEL_FROM_GEO(MODEL_HF_BOO, hf_boo_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HF_GOO, hf_goo_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HF_CRYSTAL, hf_crystal_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HF_CRYSTAL_PLAT, hf_crystal_block_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HF_ICE, hf_ice_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HF_ICE_POLE, hf_ice_pole_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_HF_ICE_POLE2, hf_ice_pole2_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, hf_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf0, LEVEL_CASTLE_COURTYARD, 0x01, 0x24, WARP_NO_CHECKPOINT),
		WARP_NODE(0xf1, LEVEL_CASTLE_GROUNDS, 0x01, 0x34, WARP_NO_CHECKPOINT),
		MARIO_POS(0x01, 0, -6623, 6409, 2123),
		OBJECT(MODEL_BLUE_COIN, -5750, 5489, -2160, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5750, 5152, -2160, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5750, 4613, -2160, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5750, 4047, -2160, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5750, 3473, -2160, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5750, 2841, -2160, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5750, 2308, -2160, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5054, 2006, -2167, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -4376, 1611, -1703, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -4384, 1611, -2228, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -4383, 1611, -2812, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_BLUE_COIN, -5268, 5489, -2160, 0, 0, 0, 0x00000000, bhvHiddenBlueCoin),
		OBJECT(MODEL_HF_BOO, -545, 428, 6897, 0, 0, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_HF_BOO, 582, 726, 6897, 0, -90, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_HF_BOO, 582, 815, 7857, 0, -43, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_HF_BOO, 582, 1674, 7857, 0, 136, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_HF_BOO, -97, 1658, 7109, 0, 89, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_HF_BOO, -85, 1876, 6289, 0, 89, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_HF_GOO, 3441, 2314, 6122, 0, 0, 0, 0x00000000, bhvHfGoo),
		OBJECT(MODEL_HF_GOO, 3908, 2314, 7277, 0, 0, 0, 0x00000000, bhvHfGoo),
		OBJECT(MODEL_HF_GOO, 5461, 2314, 7685, 0, 0, 0, (1 << 16), bhvHfGoo),
		OBJECT(MODEL_HF_GOO, 7270, 2314, 7356, 0, 0, 0, (2 << 16), bhvHfGoo),
		OBJECT(MODEL_HF_GOO, 8241, 2314, 7439, 0, 0, 0, 0x00000000, bhvHfGoo),
		OBJECT(MODEL_HF_GOO, 9968, 2314, 7878, 0, 0, 0, (2 << 16), bhvHfGoo),
		OBJECT(MODEL_HF_BOO, 9270, 2459, 10206, 0, 144, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_HF_BOO, 8388, 2596, 9625, 0, -146, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_HF_BOO, 7661, 2832, 9913, 0, -178, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_EXCLAMATION_BOX, -6856, 2211, -5272, 0, 0, 0, (2 << 16), bhvExclamationBox),
		OBJECT(MODEL_HF_BOO, 122, 2280, -3473, 0, 125, 0, 0x00000000, bhvHfBoo),
		OBJECT(MODEL_NONE, -2000, 2678, -11611, 0, -43, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 50, 0, 7097, 0, 0, 0, 0x00000000, bhvHfBooCtl),
		OBJECT(MODEL_CHUCKYA, -7303, 1803, -2155, 0, 0, 0, 0x00000000, bhvChuckya),
		OBJECT(MODEL_NONE, -5104, 6531, 2081, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 2756, 1508, -2718, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -1841, 2678, -12186, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 36, 0, 7092, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -6915, 1803, -3203, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, -3962, 1471, -92, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 920, 1350, -1962, 0, 0, 0, (2 << 16), bhvCoinFormation),
		OBJECT(MODEL_NONE, 1320, 1790, 1088, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_HF_CRYSTAL, 3488, 2188, -3571, 0, 0, 0, 0x00000000, bhvHfCrystal),
		OBJECT(MODEL_EXCLAMATION_BOX, -13240, 2746, 1233, 0, 0, 0, (3 << 16), bhvExclamationBox),
		OBJECT(MODEL_STAR, -4375, 1322, -14993, 0, 0, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_EXCLAMATION_BOX, 5247, 1989, 1788, 0, 0, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -1641, 1374, 3492, 0, 0, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -1343, 1225, 5249, 0, 0, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -927, 985, 8588, 0, 0, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, 1804, 4432, 74, 0, 0, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_EXCLAMATION_BOX, -6981, 3923, -2194, 0, 0, 0, (6 << 16), bhvExclamationBox),
		OBJECT(MODEL_BLUE_COIN_SWITCH, -5268, 5048, -2160, 0, 0, 0, 0x00000000, bhvBlueCoinSwitch),
		OBJECT(MODEL_BLUE_COIN_SWITCH, 3440, 4336, 3202, 0, 0, 0, 0x00000000, bhvBlueCoinSwitch),
		OBJECT(MODEL_NONE, -3195, 2678, -4628, 0, -43, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 902, 1350, -1822, 0, -43, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_NONE, 3610, 1835, 1392, 0, -43, 0, 0x00000000, bhvGoombaTripletSpawner),
		OBJECT(MODEL_HF_ICE, -7472, 6572, 24, 0, 14, 0, 0x00000000, bhvHfIce),
		OBJECT(MODEL_HF_ICE_POLE, -8393, 6513, -2049, 0, 14, 0, 0x00000000, bhvHfIcePole),
		OBJECT(MODEL_HF_ICE_POLE2, -5928, 8663, 37, 0, 0, 0, 0x00000000, bhvHfIcePole2),
		OBJECT(MODEL_NONE, -1941, 2678, -3946, 0, 1, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_BOO, 900, 1350, -1979, 0, 0, 0, 0x00000000, bhvBoo),
		OBJECT(MODEL_BOO, -7453, 3271, -3351, 0, 0, 0, 0x00000000, bhvBoo),
		OBJECT(MODEL_BOO, -7464, 2888, -5223, 0, 0, 0, 0x00000000, bhvBoo),
		OBJECT(MODEL_BOO, -1876, 1964, -1986, 0, 0, 0, 0x00000000, bhvBoo),
		OBJECT(MODEL_BOO, 1077, 1449, -1427, 0, 0, 0, 0x00000000, bhvBoo),
		OBJECT(MODEL_THWOMP, -2701, 2678, -6304, 0, -90, 0, 0x00000000, bhvThwomp),
		OBJECT(MODEL_THWOMP, -2701, 2678, -7022, 0, -90, 0, (1 << 16), bhvThwomp),
		OBJECT(MODEL_THWOMP, -2701, 2678, -7718, 0, -90, 0, (2 << 16), bhvThwomp),
		OBJECT(MODEL_THWOMP, -2701, 2678, -8381, 0, -90, 0, (3 << 16), bhvThwomp),
		OBJECT(MODEL_THWOMP, -2701, 2678, -9056, 0, -90, 0, (4 << 16), bhvThwomp),
		OBJECT(MODEL_THWOMP, -2701, 2678, -9730, 0, -90, 0, (5 << 16), bhvThwomp),
		OBJECT(MODEL_THWOMP, -2701, 2678, -10527, 0, -90, 0, (6 << 16), bhvThwomp),
		OBJECT(MODEL_HF_CRYSTAL, 3488, 2188, -1942, 0, 0, 0, 0x00000000, bhvHfCrystal),
		TERRAIN(hf_area_1_collision),
		MACRO_OBJECTS(hf_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_C4),
		TERRAIN_TYPE(TERRAIN_SPOOKY),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -6623, 6409, 2123),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
