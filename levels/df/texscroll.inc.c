void scroll_sts_mat_df_dl_lavalflow() {
	Gfx *mat = segmented_to_virtual(mat_df_dl_lavalflow);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_df_dl_water() {
	Gfx *mat = segmented_to_virtual(mat_df_dl_water);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_df_dl_lavahang() {
	Gfx *mat = segmented_to_virtual(mat_df_dl_lavahang);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_df() {
	scroll_sts_mat_df_dl_lavalflow();
	scroll_sts_mat_df_dl_water();
	scroll_sts_mat_df_dl_lavahang();
}
