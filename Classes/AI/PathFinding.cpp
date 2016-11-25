#include "PathFinding.h"
#include "Player.h"
#include "Game.h"

USING_NS_CC;

PathFinding::PathFinding(Player* player)
{
	this->player = player;
	gameLayer = dynamic_cast<Game*>(player->getParent());
}

PathFinding::~PathFinding()
{
}

void PathFinding::findPath(Point startPosition, Point endPosition)
{
	NodeLocation *startNode = new NodeLocation();
	startNode->initWithPosition(startPosition);
	startNode->autorelease();

	startPosition = gameLayer->worldToTilePosition(startPosition);
	endPosition = gameLayer->worldToTilePosition(endPosition);
	this->startPosition = startPosition;
	this->endPosition - endPosition;

	if (startPosition == endPosition)
		return;

	addPathToOpen(startNode);

	do {
		
	} while (_spOpenSteps.size() > 0);

}

void PathFinding::addPathToOpen(PathFinding::NodeLocation *path)
{
	int stepFScore = path->getFScore();
	ssize_t count = _spOpenSteps.size();
	ssize_t i = 0;
	for (; i < count; ++i)
	{
		if (stepFScore <= _spOpenSteps.at(i)->getFScore())
		{
			break;
		}
	}
	_spOpenSteps.insert(i, path);
}


bool PathFinding::pathExists(const cocos2d::Vector<PathFinding::NodeLocation *> &steps, const PathFinding::NodeLocation *step)
{
	for (ssize_t i = 0; i < steps.size(); ++i)
	{
		if (steps.at(i)->isEqual(step))
		{
			return true;
		}
	}
	return false;
}

int PathFinding::calculateHScore(const Point &fromPosition, const Point &toPosition)
{
	return abs(toPosition.x - fromPosition.x) + abs(toPosition.y - fromPosition.y);
}

int PathFinding::calculateMoveCost(const NodeLocation *fromStep, const NodeLocation *toStep)
{
	return ((fromStep->getPosition().x != toStep->getPosition().x)
		&& (fromStep->getPosition().y != toStep->getPosition().y)) ? 14 : 10;
}

PathFinding::NodeLocation::NodeLocation() :
	_position(Point::ZERO),
	_gScore(0),
	_hScore(0),
	_parent(nullptr)
{
}

void PathFinding::NodeLocation::initWithPosition(Point startPosition)
{
	this->position = startPosition;
}

bool PathFinding::NodeLocation::isEqual(const PathFinding::NodeLocation *other) const
{
	return this->getPosition() == other->getPosition();
}