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
#include "levels/sa/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_sa_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _sa_segment_7SegmentRomStart, _sa_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _inside_yay0SegmentRomStart, _inside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group4_yay0SegmentRomStart, _group4_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group4_geoSegmentRomStart, _group4_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group13_yay0SegmentRomStart, _group13_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group13_geoSegmentRomStart, _group13_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, sa_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 95, 2203, 1569, 0, 0, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -563, 3712, 338, 0, 0, 0, (0 << 24) | (1 << 16) | (0 << 8) | (0), bhvCoinFormation),
		OBJECT(MODEL_NONE, -563, 3712, -162, 0, 0, 0, (0 << 24) | (1 << 16) | (0 << 8) | (0), bhvCoinFormation),
		OBJECT(MODEL_NONE, 1935, 2745, 88, 0, 0, 0, (0 << 24) | (1 << 16) | (0 << 8) | (0), bhvCoinFormation),
		OBJECT(MODEL_NONE, 331, 1367, -22, 0, -15, 0, 0x00000000, bhvCoinFormation),
		OBJECT(MODEL_NONE, -500, 1567, -1777, 0, 0, 0, (0 << 24) | (2 << 16) | (0 << 8) | (0), bhvCoinFormation),
		OBJECT(MODEL_NONE, 1333, 2892, 88, 0, 0, 0, (0 << 24) | (2 << 16) | (0 << 8) | (0), bhvCoinFormation),
		OBJECT(MODEL_NONE, 101, 3635, 88, 0, 0, 0, (0 << 24) | (0b10010 << 16) | (0 << 8) | (0), bhvCoinFormation),
		OBJECT(MODEL_NONE, -1665, 5593, 88, 0, 0, 0, (0 << 24) | (1 << 16) | (0 << 8) | (0), bhvCoinFormation),
		OBJECT(MODEL_NONE, 0, 3595, 0, 0, 0, 0, 0x00000000, bhvGearSounds),
		OBJECT(MODEL_AGT_GEARKURO, 790, 466, -115, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_AGT_GEARKURO, -74, 312, 125, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_AGT_GEARKURO, -500, 1567, -1777, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_AGT_GEARKURO, 1208, 3784, 84, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_AGT_GEARKURO, 101, 4666, 1284, 0, 0, 0, 0x00000000, bhvFireSpitter),
		OBJECT(MODEL_AGT_GEARKURO, 101, 4666, -1116, 0, 0, 0, 0x00000000, bhvFireSpitter),
		MARIO_POS(0x01, -180, 0, 200, 1500),
		OBJECT(MODEL_STAR, 0, 6885, 0, 0, 0, 0, 0x00000000, bhvStar),
		OBJECT(MODEL_NONE, 0, 200, 1500, 0, -180, 0, 0x000A0000, bhvSpinAirborneWarp),
		OBJECT(MODEL_AGT_GEAR2, 100, 3443, 85, 0, 0, 0, 0x00000000, bhvAgtGear2),
		OBJECT(MODEL_AGT_GEAR3, -794, 4331, 85, 0, 0, 0, 0x00000000, bhvAgtGear3),
		OBJECT(MODEL_AGT_GEAR4, -1666, 5224, 85, 0, 0, 0, 0x00000000, bhvAgtGear4),
		TERRAIN(sa_area_1_collision),
		MACRO_OBJECTS(sa_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_AGT),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -180, 0, 200, 1500),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
