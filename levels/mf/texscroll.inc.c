void scroll_sts_mat_mf_dl_f3d_material_001() {
	Gfx *mat = segmented_to_virtual(mat_mf_dl_f3d_material_001);
	shift_s(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_mf() {
	scroll_sts_mat_mf_dl_f3d_material_001();
}
