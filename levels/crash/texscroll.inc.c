void scroll_sts_mat_crash_dl_water_bttom() {
	Gfx *mat = segmented_to_virtual(mat_crash_dl_water_bttom);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_sts_mat_crash_dl_water() {
	Gfx *mat = segmented_to_virtual(mat_crash_dl_water);
	shift_t(mat, 18, PACK_TILESIZE(0, 1));
};

void scroll_crash_dl_tube_001_mesh_layer_1_vtx_0() {
	int i = 0;
	int count = 464;
	int width = 64 * 0x20;
	int height = 64 * 0x20;

	static int currentX = 0;
	int deltaX;
	Vtx *vertices = segmented_to_virtual(crash_dl_tube_001_mesh_layer_1_vtx_0);

	deltaX = (int)(0.07000002264976501 * 0x20) % width;

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;
}

void scroll_crash() {
	scroll_sts_mat_crash_dl_water_bttom();
	scroll_sts_mat_crash_dl_water();
	scroll_crash_dl_tube_001_mesh_layer_1_vtx_0();
}
