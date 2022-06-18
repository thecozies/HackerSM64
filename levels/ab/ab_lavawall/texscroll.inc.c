void scroll_sts_mat_ab_lavawall__16_f3d_layer5() {
	Gfx *mat = segmented_to_virtual(mat_ab_lavawall__16_f3d_layer5);
	shift_s(mat, 13, PACK_TILESIZE(0, 2));
	shift_t_down(mat, 21, PACK_TILESIZE(0, 1));
};

void scroll_ab_level_geo_ab_lavawall() {
	scroll_sts_mat_ab_lavawall__16_f3d_layer5();
}
