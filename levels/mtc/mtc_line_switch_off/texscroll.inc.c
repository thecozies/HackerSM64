void scroll_sts_mat_mtc_line_switch_off_f3d_material_001() {
	Gfx *mat = segmented_to_virtual(mat_mtc_line_switch_off_f3d_material_001);
	shift_t(mat, 11, PACK_TILESIZE(0, 1));
};

void scroll_mtc_level_geo_mtc_line_switch_off_set(SetTileSize* ts)
{
	SetTileSize *mat = segmented_to_virtual(mat_mtc_line_switch_off_f3d_material_001);
	mat += 11;
	mat->u = ts->u;
	mat->v = ts->v;
	mat->s = ts->s;
	mat->t = ts->t;
}

void scroll_mtc_level_geo_mtc_line_switch_off() {
	scroll_sts_mat_mtc_line_switch_off_f3d_material_001();
}
