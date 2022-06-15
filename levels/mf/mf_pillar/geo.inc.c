#include "src/game/envfx_snow.h"

const GeoLayout mf_pillar_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_pillar_Makai_Flower_Gardens_011_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mf_pillar_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
