#include <entityx/entityx.h>
#include "cocos2d.h"
#include "Components/RapidComponents.h"

struct MovementSystem : public entityx::System<MovementSystem> {
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<SpriteComponent, PhysicsBodyComponent, CreatureComponent>([dt](entityx::Entity entity, SpriteComponent &sprite, PhysicsBodyComponent &physicsBody, CreatureComponent &creature) {
			sprite.sprite->setPosition(cocos2d::Point(physicsBody.physicsBody->GetPosition().x * 32, physicsBody.physicsBody->GetPosition().y * 32));
			sprite.label->setPosition(cocos2d::Point(sprite.sprite->getPosition().x + 3, sprite.sprite->getPosition().y + 60));
			creature.bar->setBarPosition(cocos2d::Point(sprite.sprite->getPosition().x - 55, sprite.sprite->getPosition().y + 30));
		});
	};
};