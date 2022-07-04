#include "src/game/envfx_snow.h"

const GeoLayout ow_part_brodute[] = {
	GEO_CULLING_RADIUS(30000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ow_part_brodute_part_brodute_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, ow_part_brodute_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
