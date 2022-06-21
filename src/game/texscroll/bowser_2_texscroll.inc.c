#include "levels/bowser_2/header.h"
#include "levels/bowser_2/texscroll.inc.c"
#include "levels/bowser_2/fight_plat_shadow/texscroll.inc.c"
#include "levels/bowser_2/fight_bomb/texscroll.inc.c"
void scroll_textures_bowser_2() {
	scroll_bowser_2();
	scroll_bowser_2_level_geo_fight_plat_shadow();
	scroll_bowser_2_level_geo_fight_bomb();
}
