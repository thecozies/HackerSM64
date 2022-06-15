void scroll_sts_mat_hf_scary_boo_lines_boom_layer1() {
	Gfx *mat = segmented_to_virtual(mat_hf_scary_boo_lines_boom_layer1);
	shift_t(mat, 13, PACK_TILESIZE(0, 1));
};

void scroll_hf_level_dl_hf_scary_boo_lines() {
	scroll_sts_mat_hf_scary_boo_lines_boom_layer1();
}
