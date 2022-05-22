#include "src/game/envfx_snow.h"

const GeoLayout mtc_line_whole_geo[] = {
	GEO_CULLING_RADIUS(9000),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mtc_line_whole_Plane_001_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mtc_line_whole_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
