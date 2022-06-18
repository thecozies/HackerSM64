#include "src/game/envfx_snow.h"

const GeoLayout df_arrow_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, df_arrow_Plane_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, df_arrow_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
