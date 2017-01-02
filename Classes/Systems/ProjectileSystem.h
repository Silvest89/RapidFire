#include <entityx/entityx.h>
#include "cocos2d.h"
#include "Components/RapidComponents.h"

struct ProjectileSystem : public entityx::System<ProjectileSystem> {
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<BulletComponent, MovementComponent>([dt](entityx::Entity entity, BulletComponent &bulletCP, MovementComponent &creature) {
			float angle = bulletCP.angle;
			Vec2 origin = bulletCP.origin;
			int speed = bulletCP.speed;
			Vec2 currentPosition = bulletCP.bulletSprite->getPosition();

			Vec2 newPosition(currentPosition.x + speed * cos(angle) * dt, currentPosition.y + speed * sin(angle) * dt);

			//CCLOG("test");
			bulletCP.bulletSprite->setPosition(newPosition);



		});
	};
};