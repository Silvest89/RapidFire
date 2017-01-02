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
		es.each<InputComponent, SkeletonComponent, MovementComponent, WeaponComponent>([dt, this](entityx::Entity entity, InputComponent &input, SkeletonComponent &skeletonCP, MovementComponent &movementCP, WeaponComponent &weaponCP) {
			this->movementCP = &movementCP;
			this->skeletonCP = &skeletonCP;

			weaponCP.fireRateTimer += dt;

			if (input.controller->rightJoystick->getDegrees() != 0.0f)
			{
				float angle = input.controller->rightJoystick->getDegrees();
				bool canFire = false;
				if (skeletonCP.skeleton->getScaleX() == -1)
				{
					if (angle > 130 && angle < 230)
					{
						spBone *rearBracer = skeletonCP.skeleton->findBone("gun");
						rearBracer->data->rotation = 180 - angle;
						skeletonCP.skeleton->updateWorldTransform();
						canFire = true;
					}
				}
				else
				{
					if (angle < 50 || angle > 310)
					{
						spBone *rearBracer = skeletonCP.skeleton->findBone("gun");

						rearBracer->data->rotation = angle;
						skeletonCP.skeleton->updateWorldTransform();
						canFire = true;
					}
				}
				if (weaponCP.fireRateTimer >= weaponCP.getFireRate() && canFire)
				{ 
					weaponCP.fireRateTimer = 0;
					//skeletonCP.skeleton->update(0.0f);
					spBone *upperArm = skeletonCP.skeleton->findBone("angleCalc");
					spBone *gunTip = skeletonCP.skeleton->findBone("gunTip");
					float upperX, upperY;
					float rearX, rearY;
					float offset;

					if (skeletonCP.skeleton->getScaleX() == 1)
					{
						upperX = skeletonCP.skeleton->getPositionX() + upperArm->worldX;
						upperY = skeletonCP.skeleton->getPositionY() + upperArm->worldY;

						rearX = skeletonCP.skeleton->getPositionX() + gunTip->worldX;
						rearY = skeletonCP.skeleton->getPositionY() + gunTip->worldY;
						offset = -angle + 20;
					}
					else
					{
						upperX = skeletonCP.skeleton->getPositionX() - upperArm->worldX;
						upperY = skeletonCP.skeleton->getPositionY() + upperArm->worldY;

						rearX = skeletonCP.skeleton->getPositionX() - gunTip->worldX;
						rearY = skeletonCP.skeleton->getPositionY() + gunTip->worldY;
						offset = -angle - 20;
					}

					Vec2 position = skeletonCP.skeleton->getPosition();
					float angle2 = atan2(rearY - upperY, rearX - upperX);

					entity = Game::ex.entities.create();
			
					entity.assign<BulletComponent>(WEAPON_PISTOL, angle2, Vec2(rearX, rearY), offset);
					entity.assign<MovementComponent>();
					//entityx::Entity playerEntity = ex.entities.create();
				}
			}

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