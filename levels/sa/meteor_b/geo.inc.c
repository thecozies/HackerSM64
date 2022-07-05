#include "src/game/envfx_snow.h"

const GeoLayout meteor_b_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, meteor_b_meteor_b_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, meteor_b_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
