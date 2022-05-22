void scroll_sts_mat_mtc_line_inactive_f3d_material() {
	Gfx *mat = segmented_to_virtual(mat_mtc_line_inactive_f3d_material);
	shift_t(mat, 11, PACK_TILESIZE(0, 1));
};

void scroll_mtc_level_geo_mtc_line_inactive_set(SetTileSize* ts)
{
	SetTileSize *mat = segmented_to_virtual(mat_mtc_line_inactive_f3d_material);
	mat += 11;
	mat->u = ts->u;
	mat->v = ts->v;
	mat->s = ts->s;
	mat->t = ts->t;
}

void scroll_mtc_level_geo_mtc_line_inactive() {
	scroll_sts_mat_mtc_line_inactive_f3d_material();
}
