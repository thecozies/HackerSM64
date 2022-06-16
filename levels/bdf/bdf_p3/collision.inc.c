const Collision bdf_p3_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(14),
	COL_VERTEX(-471, -71, -236),
	COL_VERTEX(-236, -306, 0),
	COL_VERTEX(-471, -71, 236),
	COL_VERTEX(236, -306, 0),
	COL_VERTEX(471, -71, -236),
	COL_VERTEX(471, -71, 236),
	COL_VERTEX(471, 47, -236),
	COL_VERTEX(471, 47, 236),
	COL_VERTEX(-471, 47, -236),
	COL_VERTEX(-471, 47, 236),
	COL_VERTEX(-412, 47, 177),
	COL_VERTEX(-412, 47, -177),
	COL_VERTEX(412, 47, -177),
	COL_VERTEX(412, 47, 177),
	COL_TRI_INIT(SURFACE_DEFAULT, 24),
	COL_TRI(0, 1, 2),
	COL_TRI(3, 1, 0),
	COL_TRI(3, 0, 4),
	COL_TRI(1, 3, 5),
	COL_TRI(1, 5, 2),
	COL_TRI(5, 3, 4),
	COL_TRI(5, 4, 6),
	COL_TRI(5, 6, 7),
	COL_TRI(4, 0, 8),
	COL_TRI(4, 8, 6),
	COL_TRI(0, 2, 9),
	COL_TRI(0, 9, 8),
	COL_TRI(7, 9, 2),
	COL_TRI(7, 2, 5),
	COL_TRI(10, 9, 7),
	COL_TRI(9, 10, 8),
	COL_TRI(11, 8, 10),
	COL_TRI(8, 11, 6),
	COL_TRI(6, 11, 12),
	COL_TRI(12, 11, 10),
	COL_TRI(12, 10, 13),
	COL_TRI(10, 7, 13),
	COL_TRI(13, 7, 12),
	COL_TRI(6, 12, 7),
	COL_TRI_STOP(),
	COL_END()
};