#include "src/game/envfx_snow.h"

const GeoLayout mf_help_geo[] = {
	GEO_CULLING_RADIUS(900),
	GEO_OPEN_NODE(),
         GEO_BILLBOARD(),
         GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mf_help_Plane_011_mesh_layer_4),
		GEO_DISPLAY_LIST(LAYER_ALPHA, mf_help_material_revert_render_settings),
         GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
