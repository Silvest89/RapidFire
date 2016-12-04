#ifndef __PHYSICSBODYCOMPONENT_H__
#define __PHYSICSBODYCOMPONENT_H__

#include "cocos2d.h"
#include "Player.h"
#include "Game.h"
#include "Box2D\Box2D.h"

struct PhysicsBodyComponent {
	PhysicsBodyComponent(Player *player)
	{
		// Body of the ball
		b2BodyDef bodyDef; // Define the above Body
		b2FixtureDef fixtureDef; // Define some static features: friction, restitution, density, etc.
		b2PolygonShape bodyShape; // the shape of body
		b2FixtureDef fixtureDef2;
		bodyShape.SetAsBox(1.5f, 3.5f);

		//fixtureDef
		fixtureDef.density = 0.0f;
		fixtureDef.friction = 0.0f;
		fixtureDef.restitution = 0.0f;
		fixtureDef.filter.categoryBits = CATEGORY_PLAYER;
		fixtureDef.filter.maskBits = CATEGORY_STATIC;
		fixtureDef.shape = &bodyShape; // point to bodyShape

									   //bodyDef
		bodyDef.type = b2_dynamicBody; // Dynamic collision
		bodyDef.userData = player; // Attach to Sprite ball

								   // Set position, and remember to convert the unit
		bodyDef.position.Set(player->getPosition().x / 32, player->getPosition().y / 32);

		//add radar sensor to ship
		b2PolygonShape foot;
		foot.SetAsBox(1.0f, 0.1f, b2Vec2(0, -3.7f), 0);
		fixtureDef2.shape = &foot;
		fixtureDef2.isSensor = true;
		fixtureDef2.filter.categoryBits = GROUND_SENSOR;
		fixtureDef2.filter.maskBits = CATEGORY_STATIC;//radar only collides with aircraft

		

		//ballBody
		//physicsBody = Game::_game->getPhysicsWorld()->CreateBody(&bodyDef); // Create Body
		physicsBody->CreateFixture(&fixtureDef); // Create static features
		physicsBody->CreateFixture(&fixtureDef2);
		physicsBody->SetLinearDamping(1.0f);
	}

	b2Body *physicsBody;
};

#endif