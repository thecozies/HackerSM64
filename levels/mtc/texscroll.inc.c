void scroll_sts_mat_mtc_dl_LAVAFALL_f3d() {
	Gfx *mat = segmented_to_virtual(mat_mtc_dl_LAVAFALL_f3d);
	shift_t(mat, 17, PACK_TILESIZE(0, 2));
};

void scroll_sts_mat_mtc_dl__4_f3d_layer1() {
	Gfx *mat = segmented_to_virtual(mat_mtc_dl__4_f3d_layer1);
	shift_t(mat, 21, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_mtc_dl__10_f3d_layer1() {
	Gfx *mat = segmented_to_virtual(mat_mtc_dl__10_f3d_layer1);
	shift_t(mat, 21, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_mtc_dl_lava_f3d() {
	Gfx *mat = segmented_to_virtual(mat_mtc_dl_lava_f3d);
	shift_t(mat, 11, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_mtc_dl_DICDKS_layer1() {
	Gfx *mat = segmented_to_virtual(mat_mtc_dl_DICDKS_layer1);
	shift_t(mat, 21, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_mtc_dl_laval_layer1() {
	Gfx *mat = segmented_to_virtual(mat_mtc_dl_laval_layer1);
	shift_t(mat, 13, PACK_TILESIZE(0, 1));
};

void scroll_mtc() {
	scroll_sts_mat_mtc_dl_LAVAFALL_f3d();
	scroll_sts_mat_mtc_dl__4_f3d_layer1();
	scroll_sts_mat_mtc_dl__10_f3d_layer1();
	scroll_sts_mat_mtc_dl_lava_f3d();
	scroll_sts_mat_mtc_dl_DICDKS_layer1();
	scroll_sts_mat_mtc_dl_laval_layer1();
}
