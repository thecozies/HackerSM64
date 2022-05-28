const Collision hf_ice_collision[] = {
	COL_INIT(),
	COL_VERTEX_INIT(24),
	/*
	 -       +
    tA - - - B
	 |       |
	bC - - - D

	A = xt-
	B = xt+
	C = xb-
	D = xb+
	 */
	COL_VERTEX(215, 385, -72),     // +0t+ | mr, hh
	COL_VERTEX(-212, 385, -70),    // +0t- | mr, hh
	COL_VERTEX(-239, 291, 591),    // +1t- | l, h
	COL_VERTEX(249, 291, 589),     // +1t+ | l, h
	COL_VERTEX(-340, -385, 1216),  // +2t- | ll, bb
	COL_VERTEX(357, -385, 1212),   // +2t+ | ll, bb
	COL_VERTEX(-212, 180, -59),    // +0b- | ml, h
	COL_VERTEX(215, 180, -62),     // +0b+ | ml, h
	COL_VERTEX(249, 86, 453),      // +1b+ | r, h
	COL_VERTEX(-240, 86, 456),     // +1b- | r, h
	COL_VERTEX(355, -379, 822),    // +2b+ | rr, bb
	COL_VERTEX(-342, -379, 826),   // +2b- | rr, bb
	COL_VERTEX(280, 32, -558),     // -1b+ | r, m
	COL_VERTEX(279, 264, -722),    // -1t+ | r, h
	COL_VERTEX(218, 385, -78),     // -0t+ | mr, hh
	COL_VERTEX(218, 180, -67),     // -0b+ | mr, h
	COL_VERTEX(351, -373, -817),   // -2b+ | l, bb
	COL_VERTEX(349, -373, -1213),  // -2t+ | ll, bb
	COL_VERTEX(-358, -373, -1209), // -2t- | ll, bb
	COL_VERTEX(-356, -373, -813),  // -2b- | l, bb
	COL_VERTEX(-282, 32, -555),    // -1b- | r, m
	COL_VERTEX(-283, 264, -718),   // -1t- | r, h
	COL_VERTEX(-209, 180, -65),    // -0b- | mr, h
	COL_VERTEX(-209, 385, -75),    // -0t- | mr, hh
	COL_TRI_INIT(SURFACE_DEFAULT, 36),
	COL_TRI(0, 1, 2),
	COL_TRI(0, 2, 3),
	COL_TRI(3, 2, 4),
	COL_TRI(3, 4, 5),
	COL_TRI(6, 7, 8),
	COL_TRI(6, 8, 9),
	COL_TRI(7, 0, 3),
	COL_TRI(7, 3, 8),
	COL_TRI(1, 6, 9),
	COL_TRI(1, 9, 2),
	COL_TRI(9, 8, 10),
	COL_TRI(9, 10, 11),
	COL_TRI(8, 3, 5),
	COL_TRI(8, 5, 10),
	COL_TRI(2, 9, 11),
	COL_TRI(2, 11, 4),
	COL_TRI(1, 0, 7),
	COL_TRI(1, 7, 6),
	COL_TRI(12, 13, 14),
	COL_TRI(12, 14, 15),
	COL_TRI(16, 17, 13),
	COL_TRI(16, 13, 12),
	COL_TRI(18, 19, 20),
	COL_TRI(18, 20, 21),
	COL_TRI(17, 18, 21),
	COL_TRI(17, 21, 13),
	COL_TRI(19, 16, 12),
	COL_TRI(19, 12, 20),
	COL_TRI(21, 20, 22),
	COL_TRI(21, 22, 23),
	COL_TRI(13, 21, 23),
	COL_TRI(13, 23, 14),
	COL_TRI(20, 12, 15),
	COL_TRI(20, 15, 22),
	COL_TRI(23, 22, 15),
	COL_TRI(23, 15, 14),
	COL_TRI_STOP(),
	COL_END()
};

const Collision hf_ice_collision_backup[] = {
	COL_VERTEX(215, 385, -72),     // +0t+ | mr, hh
	COL_VERTEX(-212, 385, -70),    // +0t- | mr, hh
	COL_VERTEX(-239, 291, 591),    // +1t- | l, h
	COL_VERTEX(249, 291, 589),     // +1t+ | l, h
	COL_VERTEX(-340, -385, 1216),  // +2t- | ll, bb
	COL_VERTEX(357, -385, 1212),   // +2t+ | ll, bb
	COL_VERTEX(-212, 180, -59),    // +0b- | ml, h
	COL_VERTEX(215, 180, -62),     // +0b+ | ml, h
	COL_VERTEX(249, 86, 453),      // +1b+ | r, h
	COL_VERTEX(-240, 86, 456),     // +1b- | r, h
	COL_VERTEX(355, -379, 822),    // +2b+ | rr, bb
	COL_VERTEX(-342, -379, 826),   // +2b- | rr, bb
	COL_VERTEX(280, 32, -558),     // -1b+ | r, m
	COL_VERTEX(279, 264, -722),    // -1t+ | r, h
	COL_VERTEX(218, 385, -78),     // -0t+ | mr, hh
	COL_VERTEX(218, 180, -67),     // -0b+ | mr, h
	COL_VERTEX(351, -373, -817),   // -2b+ | l, bb
	COL_VERTEX(349, -373, -1213),  // -2t+ | ll, bb
	COL_VERTEX(-358, -373, -1209), // -2t- | ll, bb
	COL_VERTEX(-356, -373, -813),  // -2b- | l, bb
	COL_VERTEX(-282, 32, -555),    // -1b- | r, m
	COL_VERTEX(-283, 264, -718),   // -1t- | r, h
	COL_VERTEX(-209, 180, -65),    // -0b- | mr, h
	COL_VERTEX(-209, 385, -75),    // -0t- | mr, hh
};