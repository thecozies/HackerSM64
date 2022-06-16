Lights1 yellow_platform_yellow_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFF, 0xFF, 0xFF, 0x28, 0x28, 0x28);

Lights1 yellow_platform_gray_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFF, 0xFF, 0xFF, 0x28, 0x28, 0x28);

Vtx yellow_platform_Cube_mesh_layer_5_vtx_cull[8] = {
	{{{-100, -100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, -100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, -100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, -100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx yellow_platform_Cube_mesh_layer_5_vtx_0[24] = {
	{{{-100, -84, 84},0, {389, 987},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 84, 84},0, {603, 987},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 84, -84},0, {603, 773},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, -84, -84},0, {389, 773},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-84, -84, -100},0, {389, 731},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-84, 84, -100},0, {603, 731},{0x0, 0x0, 0x81, 0xFF}}},
	{{{84, 84, -100},0, {603, 517},{0x0, 0x0, 0x81, 0xFF}}},
	{{{84, -84, -100},0, {389, 517},{0x0, 0x0, 0x81, 0xFF}}},
	{{{100, -84, -84},0, {389, 475},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 84, -84},0, {603, 475},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 84, 84},0, {603, 261},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, -84, 84},0, {389, 261},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{84, -84, 100},0, {389, 219},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{84, 84, 100},0, {603, 219},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-84, 84, 100},0, {603, 5},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-84, -84, 100},0, {389, 5},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-84, -100, -84},0, {133, 475},{0x0, 0x81, 0x0, 0xFF}}},
	{{{84, -100, -84},0, {347, 475},{0x0, 0x81, 0x0, 0xFF}}},
	{{{84, -100, 84},0, {347, 261},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-84, -100, 84},0, {133, 261},{0x0, 0x81, 0x0, 0xFF}}},
	{{{84, 100, -84},0, {645, 475},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-84, 100, -84},0, {859, 475},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-84, 100, 84},0, {859, 261},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{84, 100, 84},0, {645, 261},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx yellow_platform_Cube_mesh_layer_5_tri_0[] = {
	gsSPVertex(yellow_platform_Cube_mesh_layer_5_vtx_0 + 0, 24, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
	gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 16, 18, 19, 0),
	gsSP2Triangles(20, 21, 22, 0, 20, 22, 23, 0),
	gsSPEndDisplayList(),
};

Vtx yellow_platform_Cube_mesh_layer_1_vtx_cull[8] = {
	{{{-100, -100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, 100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-100, -100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, -100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 100, 100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, 100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{100, -100, -100},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx yellow_platform_Cube_mesh_layer_1_vtx_0[48] = {
	{{{-100, -100, 100},0, {368, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 100, 100},0, {624, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 84, 84},0, {603, 987},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 84, -84},0, {603, 773},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, 100, -100},0, {624, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, -84, -84},0, {389, 773},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, -100, -100},0, {368, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, -84, 84},0, {389, 987},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-100, -100, -100},0, {368, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-100, 100, -100},0, {624, 752},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-84, 84, -100},0, {603, 731},{0x0, 0x0, 0x81, 0xFF}}},
	{{{84, 84, -100},0, {603, 517},{0x0, 0x0, 0x81, 0xFF}}},
	{{{100, 100, -100},0, {624, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{84, -84, -100},0, {389, 517},{0x0, 0x0, 0x81, 0xFF}}},
	{{{100, -100, -100},0, {368, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-84, -84, -100},0, {389, 731},{0x0, 0x0, 0x81, 0xFF}}},
	{{{100, -100, -100},0, {368, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 100, -100},0, {624, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 84, -84},0, {603, 475},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 84, 84},0, {603, 261},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, 100, 100},0, {624, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, -84, 84},0, {389, 261},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, -100, 100},0, {368, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, -84, -84},0, {389, 475},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{100, -100, 100},0, {368, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{100, 100, 100},0, {624, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{84, 84, 100},0, {603, 219},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-84, 84, 100},0, {603, 5},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, 100, 100},0, {624, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-84, -84, 100},0, {389, 5},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, -100, 100},0, {368, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{84, -84, 100},0, {389, 219},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-100, -100, -100},0, {112, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, -100, -100},0, {368, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{84, -100, -84},0, {347, 475},{0x0, 0x81, 0x0, 0xFF}}},
	{{{84, -100, 84},0, {347, 261},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, -100, 100},0, {368, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-84, -100, 84},0, {133, 261},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-100, -100, 100},0, {112, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-84, -100, -84},0, {133, 475},{0x0, 0x81, 0x0, 0xFF}}},
	{{{100, 100, -100},0, {624, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 100, -100},0, {880, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-84, 100, -84},0, {859, 475},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-84, 100, 84},0, {859, 261},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-100, 100, 100},0, {880, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{84, 100, 84},0, {645, 261},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{100, 100, 100},0, {624, 240},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{84, 100, -84},0, {645, 475},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx yellow_platform_Cube_mesh_layer_1_tri_0[] = {
	gsSPVertex(yellow_platform_Cube_mesh_layer_1_vtx_0 + 0, 32, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(1, 4, 3, 0, 4, 5, 3, 0),
	gsSP2Triangles(4, 6, 5, 0, 6, 7, 5, 0),
	gsSP2Triangles(6, 0, 7, 0, 0, 2, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 9, 11, 10, 0),
	gsSP2Triangles(9, 12, 11, 0, 12, 13, 11, 0),
	gsSP2Triangles(12, 14, 13, 0, 14, 15, 13, 0),
	gsSP2Triangles(14, 8, 15, 0, 8, 10, 15, 0),
	gsSP2Triangles(16, 17, 18, 0, 17, 19, 18, 0),
	gsSP2Triangles(17, 20, 19, 0, 20, 21, 19, 0),
	gsSP2Triangles(20, 22, 21, 0, 22, 23, 21, 0),
	gsSP2Triangles(22, 16, 23, 0, 16, 18, 23, 0),
	gsSP2Triangles(24, 25, 26, 0, 25, 27, 26, 0),
	gsSP2Triangles(25, 28, 27, 0, 28, 29, 27, 0),
	gsSP2Triangles(28, 30, 29, 0, 30, 31, 29, 0),
	gsSP2Triangles(30, 24, 31, 0, 24, 26, 31, 0),
	gsSPVertex(yellow_platform_Cube_mesh_layer_1_vtx_0 + 32, 16, 0),
	gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
	gsSP2Triangles(1, 4, 3, 0, 4, 5, 3, 0),
	gsSP2Triangles(4, 6, 5, 0, 6, 7, 5, 0),
	gsSP2Triangles(6, 0, 7, 0, 0, 2, 7, 0),
	gsSP2Triangles(8, 9, 10, 0, 9, 11, 10, 0),
	gsSP2Triangles(9, 12, 11, 0, 12, 13, 11, 0),
	gsSP2Triangles(12, 14, 13, 0, 14, 15, 13, 0),
	gsSP2Triangles(14, 8, 15, 0, 8, 10, 15, 0),
	gsSPEndDisplayList(),
};


Gfx mat_yellow_platform_yellow[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 255, 213, 35, 155),
	gsSPSetLights1(yellow_platform_yellow_lights),
	gsSPEndDisplayList(),
};

Gfx mat_yellow_platform_gray[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 0, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, 0),
	gsSPGeometryMode(G_CULL_BACK, 0),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetPrimColor(0, 0, 113, 113, 113, 255),
	gsSPSetLights1(yellow_platform_gray_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_yellow_platform_gray[] = {
	gsDPPipeSync(),
	gsSPGeometryMode(0, G_CULL_BACK),
	gsSPEndDisplayList(),
};

Gfx yellow_platform_Cube_mesh_layer_5[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(yellow_platform_Cube_mesh_layer_5_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_yellow_platform_yellow),
	gsSPDisplayList(yellow_platform_Cube_mesh_layer_5_tri_0),
	gsSPEndDisplayList(),
};

Gfx yellow_platform_Cube_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(yellow_platform_Cube_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_yellow_platform_gray),
	gsSPDisplayList(yellow_platform_Cube_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_yellow_platform_gray),
	gsSPEndDisplayList(),
};

Gfx yellow_platform_material_revert_render_settings[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

