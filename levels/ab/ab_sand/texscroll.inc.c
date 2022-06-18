void scroll_sts_mat_ab_sand_thingies() {
	Gfx *mat = segmented_to_virtual(mat_ab_sand_thingies);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_ab_level_geo_ab_sand() {
	scroll_sts_mat_ab_sand_thingies();
}
