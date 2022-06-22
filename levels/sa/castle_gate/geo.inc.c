#include "src/game/envfx_snow.h"

const GeoLayout castle_gate_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, castle_gate_castle_gate_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, castle_gate_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
