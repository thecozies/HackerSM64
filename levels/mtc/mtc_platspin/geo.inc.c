#include "src/game/envfx_snow.h"

const GeoLayout mtc_platspin_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mtc_platspin_Course_13_001_mesh_layer_5),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, mtc_platspin_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
