#include "src/game/envfx_snow.h"

const GeoLayout hf_bridge_mover_geo[] = {
	GEO_CULLING_RADIUS(100),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hf_bridge_mover_Plane_004_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, hf_bridge_mover_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
