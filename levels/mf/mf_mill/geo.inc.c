#include "src/game/envfx_snow.h"

const GeoLayout mf_vmill_geo[] = {
	GEO_CULLING_RADIUS(9000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_mill_C9WindmillBlade_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mf_mill_C9WindmillBlade_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_mill_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mf_mill_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
