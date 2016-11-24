#ifndef ENUMS_H_
#define ENUMS_H_

enum PhysicCollisionCategory : int {
	CATEGORY_NONE,

	CATEGORY_STATIC = 1 << 0,
	CATEGORY_PLAYER = 1 << 1,
	CATEGORY_ENEMY	= 1 << 2
};

enum AIState {
	STATE_THINKING,
	STATE_MOVETO,
	STATE_ATTACK
};

#endif