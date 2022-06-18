#include "src/game/envfx_snow.h"

const GeoLayout mf_rope_main_geo[] = {
	GEO_CULLING_RADIUS(1800),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_rope_main_Cube_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mf_rope_main_Cube_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_rope_main_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mf_rope_main_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
