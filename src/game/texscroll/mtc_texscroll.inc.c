#include "levels/mtc/header.h"
#include "levels/mtc/mtc_ball/texscroll.inc.c"
#include "levels/mtc/mtc_line_active/texscroll.inc.c"
#include "levels/mtc/mtc_line_inactive/texscroll.inc.c"
#include "levels/mtc/mtc_line_whole/texscroll.inc.c"
#include "levels/mtc/mtc_line_switch/texscroll.inc.c"
#include "levels/mtc/mtc_line_switch_off/texscroll.inc.c"
#include "levels/mtc/texscroll.inc.c"
void scroll_textures_mtc() {
	scroll_mtc_level_geo_mtc_ball();
	scroll_mtc_level_geo_mtc_line_active();
	// scroll_mtc_level_geo_mtc_line_inactive();
	scroll_mtc_level_geo_mtc_line_whole();
	scroll_mtc_level_geo_mtc_line_switch();
	// scroll_mtc_level_geo_mtc_line_switch_off();
	scroll_mtc();
}
