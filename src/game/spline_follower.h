#pragma once

#include "config/config_graphics.h"


void init_obj_spline(void);
void bhv_follow_spline(void);

#ifdef RENDER_L3D_SPLINE_LINES
void render_splines(void);

extern const Gfx sSplineLineGfx[];
extern const Gfx sResetSplineLineGfx[];
#endif // RENDER_L3D_SPLINE_LINES
