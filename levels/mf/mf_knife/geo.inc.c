#include "src/game/envfx_snow.h"

const GeoLayout mf_knife_geo[] = {
	GEO_CULLING_RADIUS(9000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_knife_Flowery_Gardens_A2_Windmill_002_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mf_knife_Flowery_Gardens_A2_Windmill_002_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_knife_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mf_knife_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
