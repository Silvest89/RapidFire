enum PhysicCollisionCategory : int {
	CATEGORY_NONE,

	CATEGORY_STATIC = 1 << 0,
	CATEGORY_PLAYER = 1 << 1,
};