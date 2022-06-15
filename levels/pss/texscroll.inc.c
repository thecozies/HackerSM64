void scroll_sts_mat_pss_dl__auto_1_f3d() {
	Gfx *mat = segmented_to_virtual(mat_pss_dl__auto_1_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_pss_dl__15_f3d() {
	Gfx *mat = segmented_to_virtual(mat_pss_dl__15_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 2));
};

void scroll_sts_mat_pss_dl_AAAAA_f3d() {
	Gfx *mat = segmented_to_virtual(mat_pss_dl_AAAAA_f3d);
	shift_t(mat, 11, PACK_TILESIZE(0, 2));
};

void scroll_pss() {
	scroll_sts_mat_pss_dl__auto_1_f3d();
	scroll_sts_mat_pss_dl__15_f3d();
	scroll_sts_mat_pss_dl_AAAAA_f3d();
}
