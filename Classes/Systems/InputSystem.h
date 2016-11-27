#include <entityx/entityx.h>
#include "Components\SpriteComponent.h"
#include "Components\InputComponent.h"
#include "Components\PhysicsBodyComponent.h"
#include "Game.h"

struct InputSystem : public entityx::System<InputSystem> {
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<InputComponent, PhysicsBodyComponent>([dt](entityx::Entity entity, InputComponent &input, PhysicsBodyComponent &physicsBody) {
			if (input.controller->leftJoystick->getVelocity().x < 0) {
				physicsBody.physicsBody->ApplyForce(b2Vec2(-8.0f, 0.0f), physicsBody.physicsBody->GetWorldCenter(), true);
			}
		   else if(input.controller->leftJoystick->getVelocity().x > 0)
			   physicsBody.physicsBody->ApplyForce(b2Vec2(8.0f, 0.0f), physicsBody.physicsBody->GetWorldCenter(), true);
			/*if (controller->jumpBtn->getValue() && player->canJump()) {
				player->getPhysicsBody()->applyImpulse(Vec2(0, 400));
				player->getPhysicsBody()->setVelocity(Vec2(0, 150));
				player->setCanJump(false);
			}*/
		});
	};
};