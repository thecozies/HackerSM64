void scroll_castle_grounds_dl_Lake_of_the_East_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 4;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(castle_grounds_dl_Lake_of_the_East_mesh_layer_5_vtx_0);

	deltaX = (int)(-0.13999998569488525 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_sts_mat_castle_grounds_dl__32_f3d() {
	Gfx *mat = segmented_to_virtual(mat_castle_grounds_dl__32_f3d);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_castle_grounds() {
	scroll_castle_grounds_dl_Lake_of_the_East_mesh_layer_5_vtx_0();
	scroll_sts_mat_castle_grounds_dl__32_f3d();
}
