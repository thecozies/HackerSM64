void scroll_sts_mat_Hanging_Plat_hang_side_layer1() {
	Gfx *mat = segmented_to_virtual(mat_Hanging_Plat_hang_side_layer1);
	shift_s(mat, 20, PACK_TILESIZE(0, 4));
};

void scroll_actor_geo_Hanging_Plat() {
	scroll_sts_mat_Hanging_Plat_hang_side_layer1();
}
