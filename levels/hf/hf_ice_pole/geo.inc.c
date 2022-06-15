#include "src/game/envfx_snow.h"

const GeoLayout hf_ice_pole_geo[] = {
	GEO_CULLING_RADIUS(2668),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hf_ice_pole_Plane_001_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hf_ice_pole_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
