#include "src/game/envfx_snow.h"

const GeoLayout ab_lavawall[] = {
	GEO_CULLING_RADIUS(1165),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ab_lavawall_Azure_Abyss2_lava_003_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ab_lavawall_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
