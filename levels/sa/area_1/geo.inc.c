#include "src/game/envfx_snow.h"

const GeoLayout sa_area_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(4, geo_switch_area),
		GEO_OPEN_NODE(),
			GEO_BRANCH(1, sa_dl_room_00_geo),
			GEO_BRANCH(1, sa_dl_room_1_geo),
			GEO_BRANCH(1, sa_dl_room_2_geo),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout sa_dl_room_00_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout sa_dl_room_1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0x00, geo_set_background_colour),
		GEO_ASM(0x00, geo_render_INFBG),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 15144, 0, 0, sa_dl_Cube_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 10498, 3100, -9, sa_dl_ground_to_area_2_visual_mesh_layer_1),
		GEO_TRANSLATE_ROTATE_WITH_DL(LAYER_OPAQUE, 14587, 4719, -9, 0, 0, 90, sa_dl_ground_to_area_2_visual_001_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 10190, 127, 0, sa_dl_teleporter_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 10818, 1027, 472, sa_dl_teleporter_001_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout sa_dl_room_2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout sa_area_1[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 30000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 0, 0, 0, -100, 0, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, sa_area_1_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sa_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
