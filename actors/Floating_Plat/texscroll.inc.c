void scroll_Floating_Plat_static_gfx_mesh_layer_5_vtx_0() {
	int i = 0;
	int count = 57;
	int width = 32 * 0x20;
	int height = 32 * 0x20;

	static int currentX = 0;
	int deltaX;
	static int timeX;
	float amplitudeX = 0.4000000059604645;
	float frequencyX = 0.6399999856948853;
	float offsetX = 0.0;
	Vtx *vertices = segmented_to_virtual(Floating_Plat_static_gfx_mesh_layer_5_vtx_0);

	deltaX = (int)(amplitudeX * frequencyX * coss((frequencyX * timeX + offsetX) * (1024 * 16 - 1) / 6.28318530718) * 0x20);

	if (absi(currentX) > width) {
		deltaX -= (int)(absi(currentX) / width) * width * signum_positive(deltaX);
	}

	for (i = 0; i < count; i++) {
		vertices[i].n.tc[0] += deltaX;
	}
	currentX += deltaX;	timeX += 1;
}

void scroll_sts_mat_Floating_Plat_flame() {
	Gfx *mat = segmented_to_virtual(mat_Floating_Plat_flame);
	shift_t(mat, 14, PACK_TILESIZE(0, 2));
	shift_t_down(mat, 22, PACK_TILESIZE(0, 4));
};

void scroll_actor_geo_Floating_Plat() {
	scroll_Floating_Plat_static_gfx_mesh_layer_5_vtx_0();
	scroll_sts_mat_Floating_Plat_flame();
}
