#include "src/game/envfx_snow.h"

const GeoLayout Floating_Plat_Geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
	GEO_ASM(GEO_TRANSPARENCY_MODE_NORMAL, geo_update_layer_transparency),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, Floating_Plat_static_gfx_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, Floating_Plat_static_gfx_mesh_layer_5),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, Floating_Plat_material_revert_render_settings),
			GEO_DISPLAY_LIST(LAYER_TRANSPARENT, Floating_Plat_material_revert_render_settings),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
