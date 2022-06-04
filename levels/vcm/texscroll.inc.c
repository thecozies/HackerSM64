void scroll_sts_mat_vcm_dl_scrollnum3_f3d() {
	Gfx *mat = segmented_to_virtual(mat_vcm_dl_scrollnum3_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_vcm_dl_scrollred_f3d() {
	Gfx *mat = segmented_to_virtual(mat_vcm_dl_scrollred_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_vcm_dl_scrollwaves_f3d() {
	Gfx *mat = segmented_to_virtual(mat_vcm_dl_scrollwaves_f3d);
	shift_t(mat, 11, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_vcm_dl_scrollredpipe_f3d() {
	Gfx *mat = segmented_to_virtual(mat_vcm_dl_scrollredpipe_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 2));
};

void scroll_vcm() {
	scroll_sts_mat_vcm_dl_scrollnum3_f3d();
	scroll_sts_mat_vcm_dl_scrollred_f3d();
	scroll_sts_mat_vcm_dl_scrollwaves_f3d();
	scroll_sts_mat_vcm_dl_scrollredpipe_f3d();
}
