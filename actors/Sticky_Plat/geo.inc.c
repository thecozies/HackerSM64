#include "src/game/envfx_snow.h"

const GeoLayout Sticky_Plat_Geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, Sticky_Plat_Cube_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, Sticky_Plat_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
