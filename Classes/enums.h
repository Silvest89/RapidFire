#ifndef ENUMS_H_
#define ENUMS_H_

enum PhysicCollisionCategory : int {
	CATEGORY_NONE,

	CATEGORY_STATIC = 1 << 0,
	CATEGORY_PLAYER = 1 << 1,
	CATEGORY_ENEMY	= 1 << 2,
	GROUND_SENSOR   = 1 << 3,
};

enum AIState {
	STATE_THINKING,
	STATE_MOVETO,
	STATE_ATTACK
};

enum AnimationState {
	STATE_FALLING,
	STATE_RUNNING,
	STATE_IDLE,
	STATE_JUMPING
};

#endif