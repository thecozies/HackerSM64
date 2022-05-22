void scroll_sts_mat_mtc_line_switch_f3d_material_001() {
	Gfx *mat = segmented_to_virtual(mat_mtc_line_switch_f3d_material_001);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

struct SetTileSize* scroll_mtc_level_geo_mtc_line_switch_get() {
	return ((SetTileSize*) segmented_to_virtual(mat_mtc_line_switch_f3d_material_001)) + 18;
}

void scroll_mtc_level_geo_mtc_line_switch() {
	scroll_sts_mat_mtc_line_switch_f3d_material_001();
}
