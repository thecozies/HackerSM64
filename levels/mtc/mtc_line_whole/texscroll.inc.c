void scroll_sts_mat_mtc_line_whole_f3d_material() {
	Gfx *mat = segmented_to_virtual(mat_mtc_line_whole_f3d_material);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_mtc_level_geo_mtc_line_whole() {
	scroll_sts_mat_mtc_line_whole_f3d_material();
}
