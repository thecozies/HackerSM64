#include <ultra64.h>
#include "sm64.h"
#include "geo_commands.h"

#include "game/level_geo.h"
#include "game/geo_misc.h"
#include "game/camera.h"
#include "game/moving_texture.h"
#include "game/screen_transition.h"
#include "game/paintings.h"

#include "make_const_nonconst.h"

#include "levels/hf/header.h"


#include "levels/hf/geo.inc.c"

#include "levels/hf/hf_boo/geo.inc.c"
#include "levels/hf/hf_goo/geo.inc.c"
#include "levels/hf/hf_crystal/geo.inc.c"
#include "levels/hf/hf_crystal_block/geo.inc.c"
#include "levels/hf/hf_ice/geo.inc.c"
#include "levels/hf/hf_ice_pole/geo.inc.c"
#include "levels/hf/hf_ice_pole2/geo.inc.c"
#include "levels/hf/hf_bridge_mover/geo.inc.c"
#include "levels/hf/hf_bridge1/geo.inc.c"
#include "levels/hf/hf_bridge2/geo.inc.c"
#include "levels/hf/hf_joel/geo.inc.c"

const GeoLayout hf_scary_boo_geo[] = {
	GEO_CULLING_RADIUS(2668),
    GEO_OPEN_NODE(),
    GEO_SWITCH_CASE(9, geo_switch_anim_state),
    GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hf_scary_boo0_Plane_005_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hf_scary_boo1_Plane_005_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hf_scary_boo2_Plane_005_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hf_scary_boo3_Plane_005_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hf_scary_boo4_Plane_005_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hf_scary_boo5_Plane_005_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hf_scary_boo6_Plane_005_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hf_scary_boo7_Plane_005_mesh),
		GEO_DISPLAY_LIST(LAYER_TRANSPARENT, hf_scary_jerma_Plane_005_mesh),
	GEO_CLOSE_NODE(),
	GEO_TRANSLATE_NODE_WITH_DL(LAYER_TRANSPARENT, -20, 0, 0, hf_scary_boo_lines_Plane_005_mesh),
	GEO_CLOSE_NODE(),
    GEO_END(),
};
