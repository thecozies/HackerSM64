#include "src/game/envfx_snow.h"

const GeoLayout mf_vine2_geo[] = {
	GEO_CULLING_RADIUS(900),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_vine2_string_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_vine2_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
