#include "src/game/envfx_snow.h"

const GeoLayout hf_bridge2_geo[] = {
	GEO_CULLING_RADIUS(4000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hf_bridge2_c5_004_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, hf_bridge2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
