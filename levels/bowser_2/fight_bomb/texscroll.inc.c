void scroll_sts_mat_fight_bomb_f3d_material_002() {
	Gfx *mat = segmented_to_virtual(mat_fight_bomb_f3d_material_002);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_bowser_2_level_geo_fight_bomb() {
	scroll_sts_mat_fight_bomb_f3d_material_002();
}
