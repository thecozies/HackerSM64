#ifndef SA_HEADER_H
#define SA_HEADER_H

#include "types.h"

// geo
extern const GeoLayout sa_geo_000170[];

// leveldata
extern const Gfx sa_seg7_dl_07002DE8[];
extern const Gfx sa_seg7_dl_07002FD0[];
extern const Collision sa_seg7_collision[];
extern const MacroObject sa_seg7_macro_objs[];

// script
extern const LevelScript level_sa_entry[];


#include "levels/sa/header.inc.h"

#include "levels/sa/galaxy_background/header.h"

#include "levels/sa/blinking_platform/geo_header.h"

#include "levels/sa/blinking_platform/collision_header.h"

#include "levels/sa/meteor_a/geo_header.h"

#include "levels/sa/meteor_b/geo_header.h"

#include "levels/sa/castle_gate/geo_header.h"

#include "levels/sa/castle_gate/collision_header.h"

#include "levels/sa/sunset_background/header.h"

#endif
