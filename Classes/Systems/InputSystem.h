#include <entityx/entityx.h>
#include "Components\SpriteComponent.h"
#include "Components\InputComponent.h"
#include "Game.h"
#include "cocos2d.h"
#include <algorithm>
USING_NS_CC;

struct InputSystem : public entityx::System<InputSystem> {

	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<InputComponent, PhysicsBodyComponent>([dt](entityx::Entity entity, InputComponent &input, PhysicsBodyComponent &physicsBody) {
			b2Vec2 vel = physicsBody.physicsBody->GetLinearVelocity();
			vel.x = 0;
			if (input.controller->leftJoystick->getVelocity().x < 0) {
				vel.x = -5;
				//physicsBody.physicsBody->ApplyForce(b2Vec2(-8.0f, 0.0f), physicsBody.physicsBody->GetWorldCenter(), true);
			}
			else if (input.controller->leftJoystick->getVelocity().x > 0)
			{
				vel.x = 5;
				//physicsBody.physicsBody->ApplyForce(b2Vec2(8.0f, 0.0f), physicsBody.physicsBody->GetWorldCenter(), true);
			}
			physicsBody.physicsBody->SetLinearVelocity(vel);


			if (input.controller->jumpBtn->getValue()) {
				physicsBody.physicsBody->ApplyLinearImpulseToCenter(b2Vec2(0, 10.0f), true);
				//physicsBody.physicsBody->SetLinearVelocity(b2Vec2(0, 8.0f));
				//physicsBody.physicsBody->SetLinearVelocity
			}
			/*//b2Vec2 vel = physicsBody.physicsBody->GetLinearVelocity();
			//vel.x = 0;
			Vec2 position(spriteCP.sprite->getPosition());

			spriteCP.velocity.y -= 192 * dt;
			//CCLOG("%f", spriteCP.sprite->getPositionY());
			if (spriteCP.velocity.y < 0 && -spriteCP.velocity.y > 120.0f)
			{
				spriteCP.velocity.y = (spriteCP.velocity.y > 0) ? 1 : ((spriteCP.velocity.y < 0) ? -1 : 0) * 150.0f;
			}
			//CCLOG("TEST2 %f", spriteCP.velocity.y);
			if (input.controller->leftJoystick->getVelocity().x < 0) {
				float speed = 125;
				spriteCP.velocity.x = -speed;
				CCLOG("TEST");
				//physicsBody.physicsBody->ApplyForce(b2Vec2(-8.0f, 0.0f), physicsBody.physicsBody->GetWorldCenter(), true);
			}
			else if (input.controller->leftJoystick->getVelocity().x > 0)
			{
				float speed = 128;
				spriteCP.velocity.x = speed;
				
				//physicsBody.physicsBody->ApplyForce(b2Vec2(8.0f, 0.0f), physicsBody.physicsBody->GetWorldCenter(), true);
			}

			float damping = 70 * dt;
			
			if(spriteCP.velocity.x > 0)
				spriteCP.velocity.x = spriteCP.velocity.x - damping;
			else
				spriteCP.velocity.x = spriteCP.velocity.x + damping;

			

			//physicsBody.physicsBody->SetLinearVelocity(vel);
			spriteCP.velocity.scale(dt);
			if (std::abs(spriteCP.velocity.x) < 1.0f)
				spriteCP.velocity.x = 0;
			//collideX();
			collideY(position, spriteCP);

			position.x = position.x + spriteCP.velocity.x;
			//position.y = position.y + spriteCP.velocity.y;
			CCLOG("Velocity X : %f Y: %f", spriteCP.velocity.x, spriteCP.velocity.y);
			spriteCP.sprite->setPosition(position);
			spriteCP.velocity.scale(1 / dt);

			if (input.controller->jumpBtn->getValue()) {
				CCLOG("TEST");
				spriteCP.velocity.y += 192;
				//physicsBody.physicsBody->SetLinearVelocity(b2Vec2(0, 8.0f));
				//physicsBody.physicsBody->SetLinearVelocity
			}*/

		});
	};

	/*void collideY(Vec2 &position, SpriteComponent &spriteCP) 
	{
		auto layer =Game::getMap()->getLayer("Tile Layer 1");

		auto tile = layer->getTileAt(Game::worldToTilePosition(Point(position.x, position.y + spriteCP.velocity.y)));
		if (tile)
		{
			if (spriteCP.velocity.y > 0)
				position.y = tile->getPositionY();
			else
				position.y = tile->getPositionY() + 128;;
			spriteCP.velocity.y = 0;
		}
		else
			position.y = position.y + spriteCP.velocity.y;
		
	}*/
};