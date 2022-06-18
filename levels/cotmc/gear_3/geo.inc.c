#include "src/game/envfx_snow.h"

const GeoLayout gear_3_geo[] = {
	GEO_CULLING_RADIUS(2200),
	GEO_OPEN_NODE(),
		GEO_RENDER_RANGE(-3200, 10000),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, gear_3_Cylinder_001_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, gear_3_material_revert_render_settings),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
