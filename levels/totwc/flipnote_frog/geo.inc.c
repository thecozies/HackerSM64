#include "src/game/envfx_snow.h"

const GeoLayout flipnote_frog_Material_Switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 45, flipnote_frog_Geometry_mesh_layer_4_mat_override_Frog_Blink_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout flipnote_frog_Material_Switch_opt2[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 45, flipnote_frog_Geometry_mesh_layer_4_mat_override_Frog_Croak_1_1),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout flipnote_frog_Material_Switch_opt3[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 45, flipnote_frog_Geometry_mesh_layer_4_mat_override_Frog_Croak_2_2),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout flipnote_frog_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 0, 0, 0, 90, 0),
		GEO_OPEN_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, NULL),
			GEO_OPEN_NODE(),
				GEO_SWITCH_CASE(4, geo_switch_anim_state),
				GEO_OPEN_NODE(),
					GEO_NODE_START(),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_ALPHA, 0, 0, 45, flipnote_frog_Geometry_mesh_layer_4),
					GEO_CLOSE_NODE(),
					GEO_BRANCH(1, flipnote_frog_Material_Switch_opt1),
					GEO_BRANCH(1, flipnote_frog_Material_Switch_opt2),
					GEO_BRANCH(1, flipnote_frog_Material_Switch_opt3),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_ALPHA, flipnote_frog_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
