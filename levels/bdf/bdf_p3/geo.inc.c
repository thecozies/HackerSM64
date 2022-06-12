#include "src/game/envfx_snow.h"

const GeoLayout bdf_p3_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bdf_p3_bowser_stuff_012_mesh_layer_1),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bdf_p3_bowser_stuff_012_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, bdf_p3_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, bdf_p3_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
