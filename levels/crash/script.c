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
#include "levels/crash/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_crash_entry[] = {
	INIT_LEVEL(),
	LOAD_MIO0(0x7, _crash_segment_7SegmentRomStart, _crash_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, crash_area_1),
		MARIO_POS(0x01, 0, -19608, 11877, -24734),
		OBJECT(MODEL_KOOPA_SHELL, -19355, 11877, -24474, 0, 0, 0, 0x00000000, bhvKoopaShellUnderwater),
		TERRAIN(crash_area_1_collision),
		MACRO_OBJECTS(crash_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_SEA),
		TERRAIN_TYPE(TERRAIN_WATER),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -19608, 11877, -24734),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
