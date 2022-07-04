#include "src/game/envfx_snow.h"

const GeoLayout sa_area_7_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(4, geo_switch_area),
		GEO_OPEN_NODE(),
			GEO_BRANCH(1, sa_dl_0Nothing_003_geo),
			GEO_BRANCH(1, sa_dl_Room1_geo),
			GEO_BRANCH(1, sa_dl_Room2_geo),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout sa_dl_0Nothing_003_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout sa_dl_Room1_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0x00, geo_set_background_colour),
		GEO_ASM(0x00, geo_render_INFBG),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 4654, 11226, 3549, sa_dl_EndArea6_001_mesh_layer_1),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 10125, -10491, 3549, sa_dl_EndArea6_002_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout sa_dl_Room2_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ASM(0x00, geo_render_INFBG),
		GEO_TRANSLATE_NODE_WITH_DL(LAYER_OPAQUE, 10125, -10491, -1451, sa_dl_EndArea6_003_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout sa_area_7[] = {
	GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
	GEO_OPEN_NODE(),
		GEO_ZBUFFER(1),
		GEO_OPEN_NODE(),
			GEO_CAMERA_FRUSTUM_WITH_FUNC(45.0000, 100, 30000, geo_camera_fov),
			GEO_OPEN_NODE(),
				GEO_CAMERA(CAMERA_MODE_8_DIRECTIONS, 0, 0, -600000, 0, -100, -600000, geo_camera_main),
				GEO_OPEN_NODE(),
					GEO_BRANCH(1, sa_area_7_geo),
					GEO_RENDER_OBJ(),
					GEO_ASM(ENVFX_MODE_NONE, geo_envfx_main),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, sa_dl_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
