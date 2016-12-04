#include <entityx/entityx.h>
#include "Components\RapidComponents.h"
#include "Game.h"
#include "cocos2d.h"
#include <algorithm>
USING_NS_CC;

struct InputSystem : public entityx::System<InputSystem> {
	SkeletonComponent *skeletonCP;
	MovementComponent *movementCP;
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<InputComponent, SkeletonComponent, MovementComponent>([dt, this](entityx::Entity entity, InputComponent &input, SkeletonComponent &skeletonCP, MovementComponent &movementCP) {
			this->movementCP = &movementCP;
			this->skeletonCP = &skeletonCP;
			float angle = skeletonCP.rearBracer->rotation;

			if (input.controller->leftJoystick->getVelocity().x < 0) 
			{
				movementCP.velocity.x = -256;
				skeletonCP.setState(STATE_RUNNING);
				skeletonCP.skeleton->setScaleX(-1);
				//physicsBody.physicsBody->ApplyForce(b2Vec2(-8.0f, 0.0f), physicsBody.physicsBody->GetWorldCenter(), true);
			}
			else if (input.controller->leftJoystick->getVelocity().x > 0)
			{
				movementCP.velocity.x = 256;
				skeletonCP.setState(STATE_RUNNING);
				skeletonCP.skeleton->setScaleX(1);
				//physicsBody.physicsBody->ApplyForce(b2Vec2(8.0f, 0.0f), physicsBody.physicsBody->GetWorldCenter(), true);
			}

			if (input.controller->jumpBtn->getValue()) {
				movementCP.velocity.y += 128;
				skeletonCP.setState(STATE_JUMPING);
				setGrounded(false);
			}
		});
	};

	bool isGrounded()
	{
		return skeletonCP->grounded;
	};

	void setGrounded(bool grounded)
	{
		skeletonCP->grounded = grounded;
	};
};