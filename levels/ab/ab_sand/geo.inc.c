#include "src/game/envfx_snow.h"

const GeoLayout ab_sand[] = {
	GEO_CULLING_RADIUS(2668),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ab_sand_Plane_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, ab_sand_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
