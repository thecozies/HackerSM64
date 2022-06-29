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
#include "levels/sa/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_sa_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _sa_segment_7SegmentRomStart, _sa_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _inside_yay0SegmentRomStart, _inside_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group1_yay0SegmentRomStart, _group4_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group1_geoSegmentRomStart, _group4_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group13_yay0SegmentRomStart, _group13_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group13_geoSegmentRomStart, _group13_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_2), 
	JUMP_LINK(script_func_global_14), 
	LOAD_MODEL_FROM_GEO(MODEL_BLINKING_PLATFORM, blinking_platform_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_METEOR_A, meteor_a_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_METEOR_B, meteor_b_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CASTLE_GATE, castle_gate_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, sa_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x30, LEVEL_SA, 0x01, 0x31, WARP_NO_CHECKPOINT),
		WARP_NODE(0x31, LEVEL_SA, 0x01, 0x31, WARP_NO_CHECKPOINT),
		INSTANT_WARP(0x00, 0x02, 0, 0, 0),
		OBJECT(MODEL_BLINKING_PLATFORM, 13068, 400, 0, 0, 0, 0, (0x1E << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 12768, 700, 0, 0, 0, 0, (0x1E << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 12468, 1000, 0, 0, 0, 0, (0x1E << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 10186, 1000, 0, 0, 0, 0, (0x01 << 24) | (0x1E << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 10486, 1000, 0, 0, 0, 0, (0x00 << 24) | (0x1E << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 8431, 2800, 0, 0, 0, 0, (0x01 << 24) | (20 << 8) | (60), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 9181, 3100, 0, 0, 0, 0, (0x01 << 24) | (20 << 8) | (60), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 9886, 1000, 0, 0, 0, 0, (0x02 << 24) | (0x1E << 8), bhvBlinkingPlatform),
		MARIO_POS(0x01, 0, 15144, 200, 0),
		OBJECT(MODEL_METEOR_A, 15277, 368, 2873, 0, 0, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_METEOR_B, 13332, 824, 3572, 0, 0, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_METEOR_A, 11630, 1679, 2873, 0, 0, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_METEOR_B, 9896, 1279, 4099, 0, 0, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_METEOR_B, 8224, 1750, 2041, 0, 0, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_METEOR_A, 8067, 368, -3955, 0, -180, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_METEOR_B, 10012, 824, -4653, 0, -180, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_METEOR_A, 11713, 1679, -3955, 0, -180, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_METEOR_B, 13447, 1279, -5180, 0, -180, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_METEOR_B, 15120, 1750, -3122, 0, -180, 0, 0x00000000, bhvMeteor),
		OBJECT(MODEL_NONE, 10188, 138, 11, 0, 0, 0, (0x30 << 16), bhvFadingWarp),
		OBJECT(MODEL_NONE, 10822, 2276, 485, 0, 0, 0, (0x31 << 16), bhvFadingWarp),
		OBJECT(MODEL_NONE, 15144, 200, 0, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		TERRAIN(sa_area_1_collision),
		ROOMS(sa_area_1_collision_rooms),
		MACRO_OBJECTS(sa_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_SLIDE),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(2, sa_area_2),
		INSTANT_WARP(0x00, 0x03, 0, 0, 0),
		OBJECT(MODEL_BULLET_BILL, 13644, 4590, -1057, 0, -90, 0, 0x00000000, bhvBulletBill),
		OBJECT(MODEL_BULLET_BILL, 17010, 3655, -59, 0, -90, 0, 0x00000000, bhvBulletBill),
		OBJECT(MODEL_CASTLE_GATE, 14357, 3453, -107, 0, -90, 0, 0x00000000, bhvCastleGate),
		OBJECT(MODEL_FLYGUY, 12883, 4446, -374, 0, 0, 0, 0x00000000, bhvFlyGuy),
		OBJECT(MODEL_FLYGUY, 11747, 3739, -374, 0, 0, 0, 0x00000000, bhvFlyGuy),
		OBJECT(MODEL_PURPLE_SWITCH, 14112, 4694, -95, 0, 0, 0, 0x00000000, bhvFloorSwitchHiddenObjects),
		TERRAIN(sa_area_2_collision),
		MACRO_OBJECTS(sa_area_2_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(3, sa_area_3),
		INSTANT_WARP(0x00, 0x04, -20000, -10000, 0),
		OBJECT(MODEL_BLINKING_PLATFORM, 18563, 5768, 2628, 0, 0, 0, (2 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 18563, 5768, 2928, 0, 0, 0, (2 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 18563, 5768, 3228, 0, 0, 0, (2 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 18563, 5768, 3528, 0, 0, 0, (2 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 18563, 5768, 3828, 0, 0, 0, (2 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 18563, 6068, 4128, 0, 0, 0, (1 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 18563, 6368, 4428, 0, 0, 0, (1 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 18563, 6668, 4728, 0, 0, 0, (1 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 18863, 6668, 4728, 0, 0, 0, (2 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 19163, 6668, 4728, 0, 0, 0, (2 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 19463, 6668, 4728, 0, 0, 0, (2 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 19763, 6668, 4728, 0, 0, 0, (2 << 24), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 20502, 7432, 2414, 0, 0, 0, (2 << 24) | (0x2E << 16), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 20502, 9344, -993, 0, 0, 0, (2 << 24) | (30 << 16) | (30 << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 21402, 9344, -1893, 0, 0, 0, (2 << 24) | (30 << 16) | (30 << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 20602, 10544, -3843, 0, 0, 0, (2 << 24) | (70 << 16) | (40), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 19602, 9344, -1893, 0, 0, 0, (2 << 24) | (30 << 16) | (30 << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 20502, 9344, -2793, 0, 0, 0, (2 << 24) | (30 << 16) | (30 << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 20502, 9344, -1893, 0, 0, 0, (2 << 24) | (30 << 16) | (30 << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 21402, 9344, -2793, 0, 0, 0, (2 << 24) | (30 << 16) | (30 << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 21402, 9344, -993, 0, 0, 0, (2 << 24) | (30 << 16) | (30 << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 19602, 9344, -2793, 0, 0, 0, (2 << 24) | (30 << 16) | (30 << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_BLINKING_PLATFORM, 19602, 9344, -993, 0, 0, 0, (2 << 24) | (30 << 16) | (30 << 8), bhvBlinkingPlatform),
		OBJECT(MODEL_SPRING, 20490, 6668, 2375, 0, 0, 0, (0x02 << 16), bhvSpring),
		OBJECT(MODEL_SPRING, 20490, 6668, 2957, 0, 0, 0, (0x01 << 16), bhvSpring),
		TERRAIN(sa_area_3_collision),
		MACRO_OBJECTS(sa_area_3_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	AREA(4, sa_area_4),
		OBJECT(MODEL_CASTLE_GATE, 497, 720, -11527, 0, -180, 0, (0x01 << 16), bhvCastleGate),
		TERRAIN(sa_area_4_collision),
		MACRO_OBJECTS(sa_area_4_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 15144, 200, 0),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
