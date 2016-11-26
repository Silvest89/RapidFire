#ifndef __PHYSICSBODYCOMPONENT_H__
#define __PHYSICSBODYCOMPONENT_H__
#include "cocos2d.h"
#include "chipmunk.h"
#include <entityx/entityx.h>
#include "player.h"
#include "Game.h"
#include "Box2D\Box2D.h"

b2World *Game::world = 0;

struct PhysicsBodyComponent {
	PhysicsBodyComponent(Player *player)
	{
	 // Body of the ball
		b2BodyDef bodyDef; // Define the above Body
		b2FixtureDef fixtureDef; // Define some static features: friction, restitution, density, etc.
		b2PolygonShape bodyShape; // the shape of body

		bodyShape.SetAsBox(0.5f, 0.5f);

		//fixtureDef
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.0f;
		fixtureDef.restitution = 0.2f;
		fixtureDef.filter.categoryBits = CATEGORY_PLAYER;
		fixtureDef.filter.maskBits = CATEGORY_STATIC;
		fixtureDef.shape = &bodyShape; // point to bodyShape

									   //bodyDef
		bodyDef.type = b2_dynamicBody; // Dynamic collision
		bodyDef.userData = player; // Attach to Sprite ball

								 // Set position, and remember to convert the unit
		bodyDef.position.Set(player->getPosition().x / 32, player->getPosition().y / 32);

		//ballBody
		physicsBody = Game::world->CreateBody(&bodyDef); // Create Body
		physicsBody->CreateFixture(&fixtureDef); // Create static features
		physicsBody->SetLinearDamping(1.0f);
	}

	b2Body *physicsBody;

};

#endif