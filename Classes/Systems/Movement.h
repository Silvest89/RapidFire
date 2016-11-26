#include <entityx/entityx.h>
#include "cocos2d.h"
#include "Components/AIComponent.h"

struct MovementSystem : public entityx::System<MovementSystem> {
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<SpriteComponent, PhysicsBodyComponent>([dt](entityx::Entity entity, SpriteComponent &sprite, PhysicsBodyComponent &physicsBody) {
			sprite.sprite->setPosition(cocos2d::Point(physicsBody.physicsBody->GetPosition().x * 32, physicsBody.physicsBody->GetPosition().y * 32));
			CCLOG("Speed: %f", physicsBody.physicsBody->GetLinearVelocity().x);
		});
	};
};