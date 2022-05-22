#include "src/game/envfx_snow.h"

const GeoLayout mtc_blue_rotat_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mtc_blue_rotat_Plane_003_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, mtc_blue_rotat_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
