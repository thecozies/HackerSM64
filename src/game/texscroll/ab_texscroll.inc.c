#include "levels/ab/header.h"
#include "levels/ab/texscroll.inc.c"
#include "levels/ab/ab_lavawall/texscroll.inc.c"
#include "levels/ab/ab_sand/texscroll.inc.c"
void scroll_textures_ab() {
	scroll_ab();
	scroll_ab_level_geo_ab_lavawall();
	scroll_ab_level_geo_ab_sand();
}
