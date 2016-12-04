#include <entityx/entityx.h>
#include "cocos2d.h"
#include "Components/RapidComponents.h"

struct MovementSystem : public entityx::System<MovementSystem> {
	MovementComponent *movementCP;
	SkeletonComponent *skeletonCP;
	void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override {
		es.each<SkeletonComponent, MovementComponent>([dt, this](entityx::Entity entity, SkeletonComponent &skeletonCP, MovementComponent &movementCP) {
			this->movementCP = &movementCP;
			this->skeletonCP = &skeletonCP;

			if (movementCP.velocity.y < 0 && skeletonCP.getState() != STATE_FALLING) {
				skeletonCP.setState(STATE_FALLING);
				setGrounded(false);
			}

			Vec2 position(skeletonCP.skeleton->getPosition());
			Vec2 gravity(0.0f, -128);
			gravity.scale(dt);
			movementCP.velocity = movementCP.velocity + gravity;

			float damping = (isGrounded() ? 256 : 384) * dt;

			if (movementCP.velocity.x > 0)
				movementCP.velocity.x = std::max(0.0f, movementCP.velocity.x - damping);
			else
				movementCP.velocity.x = std::min(0.0f, movementCP.velocity.x + damping);

			if (std::abs(movementCP.velocity.x) < 1.0f && isGrounded())
			{
				movementCP.velocity.x = 0;
				skeletonCP.setState(STATE_IDLE);
			}

			movementCP.velocity.scale(dt);
			collideX(position, skeletonCP);
			collideY(position, skeletonCP);
			skeletonCP.skeleton->setPosition(position + movementCP.velocity);
			movementCP.velocity.scale(1 / dt);
		});
	};

	void collideX(Vec2 &position, SkeletonComponent &skeletonCP)
	{
		Rect rect = skeletonCP.skeleton->getBoundingBox();

		auto layer = Game::getMap()->getLayer("Tile Layer 1");

		float x;
		if (movementCP->velocity.x > 0)
			x = movementCP->velocity.x + rect.size.width;
		else
			x = position.x;

		auto tile = layer->getTileAt(Game::worldToTilePosition(Point(x, position.y + 64)));
		if (tile)
		{
			if (movementCP->velocity.x > 0)
				position.x = tile->getPositionX() - rect.size.width;
			else
				position.x = tile->getPositionX() + 128;
		}
	};

	void collideY(Vec2 &position, SkeletonComponent &skeletonCP)
	{
		Rect rect = skeletonCP.skeleton->getBoundingBox();

		auto layer = Game::getMap()->getLayer("Tile Layer 1");

		float y;
		if (movementCP->velocity.y > 0)
			y = movementCP->velocity.y + rect.getMaxY();
		else
			y = position.y;

		auto tile = layer->getTileAt(Game::worldToTilePosition(Point(position.x + 64, y)));
		if (tile)
		{
			if (movementCP->velocity.y > 0)
				position.y = tile->getPositionY() - rect.size.height;
			else
			{
				position.y = tile->getPositionY() + 128;;
				setGrounded(true);
			}
			movementCP->velocity.y = 0;
		}
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