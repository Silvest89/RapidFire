#include <entityx/entityx.h>
#include "cocos2d.h"
#include "Components/RapidComponents.h"

struct RenderSystem : public entityx::System<RenderSystem> {
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<SkeletonComponent, CreatureComponent>([dt](entityx::Entity entity, SkeletonComponent &skeletonCP, CreatureComponent &creature) {
			//skeletonCP.skeleton->setPosition(cocos2d::Point(physicsBody.physicsBody->GetPosition().x * 32, physicsBody.physicsBody->GetPosition().y * 32 - 128));
			//creature.getNameLabel()->setPosition(cocos2d::Point(sprite.sprite->getPosition().x + 3, sprite.sprite->getPosition().y + 60));
			//creature.getHealthBar()->setBarPosition(cocos2d::Point(sprite.sprite->getPosition().x - 55, sprite.sprite->getPosition().y + 30));
			creature.getBar()->updateHealth(creature.getHealth(), creature.getMaxHealth());
			creature.getBar()->setPosition(cocos2d::Point(skeletonCP.skeleton->getPositionX() - 55, skeletonCP.skeleton->getPositionY() + 280));
		});
	};
};