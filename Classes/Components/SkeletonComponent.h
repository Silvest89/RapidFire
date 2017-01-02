#ifndef __SKELETONCOMPONENT_H__
#define __SKELETONCOMPONENT_H__

#include "cocos2d.h"
#include "enums.h"
#include <spine/spine-cocos2dx.h>

class Player;

USING_NS_CC;
using namespace spine;

struct SkeletonComponent {

	AnimationState animationState;
	spBone *gunTip, *rearBracer;
	bool grounded;
	//Vec2 velocity;

	SkeletonComponent(std::string skeletonFile)
	{
		skeleton = SkeletonAnimation::createWithBinaryFile("skeleton.skel", "skeleton.atlas", 0.5f);

		skeleton->setMix("idle", "run", 0.3f);
		skeleton->setMix("run", "idle", 0.1f);
		skeleton->setMix("shoot", "shoot", 0);
		skeleton->setMix("idle", "jump", 1.0f);
		gunTip = skeleton->findBone("gunTip");
		rearBracer = skeleton->findBone("rear_bracer");
		animationState = STATE_IDLE;

		skeleton->setDebugBonesEnabled(true);
		skeleton->setDebugSlotsEnabled(true);
		
	}
	SkeletonAnimation *skeleton;

	AnimationState getState()
	{
		return this->animationState;
	};

	void setState(AnimationState newState)
	{
		if (animationState == newState || newState != STATE_FALLING && !grounded)
			return;

		switch (newState)
		{
			case STATE_JUMPING:
			{
				skeleton->setAnimation(0, "jump", false);
				break;
			}
			case STATE_IDLE:
			{
				skeleton->setAnimation(0, "idle", true);
				break;
			}
			case STATE_RUNNING:
			{

				skeleton->setAnimation(0, "run", true);
				break;
			}
		}
		this->animationState = newState;
	};
};

#endif