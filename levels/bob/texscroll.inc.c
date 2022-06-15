void scroll_sts_mat_bob_dl_ghost() {
	Gfx *mat = segmented_to_virtual(mat_bob_dl_ghost);
	shift_t(mat, 11, PACK_TILESIZE(0, 12));
};

void scroll_sts_mat_bob_dl_break_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bob_dl_break_layer1);
	shift_s(mat, 19, PACK_TILESIZE(0, 2));
};

void scroll_sts_mat_bob_dl_f3d_material_002_layer1() {
	Gfx *mat = segmented_to_virtual(mat_bob_dl_f3d_material_002_layer1);
	shift_s(mat, 20, PACK_TILESIZE(0, 1));
	shift_t(mat, 20, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_bob_dl_hanging_vines() {
	Gfx *mat = segmented_to_virtual(mat_bob_dl_hanging_vines);
	shift_s(mat, 20, PACK_TILESIZE(0, 1));
	shift_t(mat, 20, PACK_TILESIZE(0, 1));
};

void scroll_bob() {
	scroll_sts_mat_bob_dl_ghost();
	scroll_sts_mat_bob_dl_break_layer1();
	scroll_sts_mat_bob_dl_f3d_material_002_layer1();
	scroll_sts_mat_bob_dl_hanging_vines();
}
