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
			
			if (input.controller->jumpBtn->getValue()) {
				CCLOG("TEST");
				physicsBody.physicsBody->ApplyLinearImpulseToCenter(b2Vec2(0, 10.0f), true);
				//physicsBody.physicsBody->SetLinearVelocity(b2Vec2(0, 8.0f));
				//physicsBody.physicsBody->SetLinearVelocity
			}

		});
	};
};