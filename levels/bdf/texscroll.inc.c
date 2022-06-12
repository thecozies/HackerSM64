void scroll_sts_mat_bdf_dl__10_f3d() {
	Gfx *mat = segmented_to_virtual(mat_bdf_dl__10_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_bdf_dl_PlatformsWaterfallRed_f3d() {
	Gfx *mat = segmented_to_virtual(mat_bdf_dl_PlatformsWaterfallRed_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_bdf_dl_PlatformsWaterfallBlue_f3d() {
	Gfx *mat = segmented_to_virtual(mat_bdf_dl_PlatformsWaterfallBlue_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_bdf_dl_PlatformsWaterfallGreen_f3d() {
	Gfx *mat = segmented_to_virtual(mat_bdf_dl_PlatformsWaterfallGreen_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_bdf_dl__auto_18_f3d() {
	Gfx *mat = segmented_to_virtual(mat_bdf_dl__auto_18_f3d);
	shift_t_down(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_bdf() {
	scroll_sts_mat_bdf_dl__10_f3d();
	scroll_sts_mat_bdf_dl_PlatformsWaterfallRed_f3d();
	scroll_sts_mat_bdf_dl_PlatformsWaterfallBlue_f3d();
	scroll_sts_mat_bdf_dl_PlatformsWaterfallGreen_f3d();
	scroll_sts_mat_bdf_dl__auto_18_f3d();
}
