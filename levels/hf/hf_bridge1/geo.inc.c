#include "src/game/envfx_snow.h"

const GeoLayout hf_bridge1_geo[] = {
	GEO_CULLING_RADIUS(2668),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hf_bridge1_c5_005_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hf_bridge1_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
