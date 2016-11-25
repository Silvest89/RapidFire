#include "cocos2d.h"

class Game;
class Player;

class PathFinding
{

public:
	PathFinding(Player* player);
	~PathFinding();

	Player* player;

	class NodeLocation : public cocos2d::Object {
	public:
		NodeLocation();
		//~NodeLocation();
		cocos2d::Point position;
		int gScore;
		int hScore;
		int jumpScore;
		NodeLocation *parent;

		bool isEqual(const NodeLocation *other) const;
		void initWithPosition(cocos2d::Point startPosition);
		int getFScore() { return gScore + hScore; };

		CC_SYNTHESIZE(cocos2d::Point, _position, Position);
		CC_SYNTHESIZE(int, _gScore, GScore);
		CC_SYNTHESIZE(int, _hScore, HScore);
		CC_SYNTHESIZE(NodeLocation*, _parent, Parent);
	};

	void findPath(cocos2d::Point startPosition, cocos2d::Point endPosition);

	cocos2d::Point startPosition, endPosition;
	bool pathExists(const cocos2d::Vector<NodeLocation*>& steps, const PathFinding::NodeLocation * step);
	int calculateMoveCost(const NodeLocation * fromStep, const NodeLocation * toStep);

private:

	cocos2d::Vector<NodeLocation*> _spOpenSteps;
	cocos2d::Vector<NodeLocation*> _spClosedSteps;
	cocos2d::Vector<NodeLocation*> _shortestPath;

	int calculateHScore(const cocos2d::Point &fromCoord, const cocos2d::Point &toCoord);
	void addPathToOpen(PathFinding::NodeLocation *path);
	Game *gameLayer;
};

