#include "InfiniteParallax.h"

USING_NS_CC;

Scene* InfiniteParallax::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = InfiniteParallax::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

InfiniteParallax::InfiniteParallax()
{
}


InfiniteParallax::~InfiniteParallax()
{
}

bool InfiniteParallax::init()
{
	//////////////////////////////
	// 1. super init first
	if (!ParallaxNode::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	sprite1 = Sprite::create("colored_grass.png");
	float scale = MAX(visibleSize.width / sprite1->getContentSize().width, visibleSize.height / sprite1->getContentSize().height);
	sprite1->setScale(scale);
	addChild(sprite1, -1, Vec2(0.0f, 0.0f), Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
	sprite2 = Sprite::create("closeNormal.png");
	sprite2->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
	addChild(sprite2, 1, Vec2(0.1f, 0.1f), Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y - 100));

	this->scheduleUpdate();

	return true;
}

void InfiniteParallax::update(float delta)
{
	auto backgroundScrollHor = Point(-1000, 0);
	setPosition(getPosition() + (backgroundScrollHor * delta));
	
	/*auto spaceDusts = new Vector<Sprite*>(1);
	spaceDusts->pushBack(sprite2);
	for (auto spaceDust : *spaceDusts) {
		float xPosition = convertToWorldSpace(spaceDust->getPosition()).x;
		float size = spaceDust->getContentSize().width;
		if (xPosition < -size / 2) {
			incrementOffset(Point(spaceDust->getContentSize().width * 20, 0), spaceDust);
		}
	}

	float xPosition = convertToWorldSpace(sprite1->getPosition()).x;
	float size = sprite1->getContentSize().width / 8;
	if (xPosition < -size) {
		incrementOffset(Point(2000, 0), sprite1);
	}*/
}

void InfiniteParallax::incrementOffset(Point offset, Node* node) {
	for (int i = 0; i < _parallaxArray->num; i++) {
		PointObject *point = (PointObject *)_parallaxArray->arr[i];
		Node * curNode = point->getChild();
		if (curNode ==/*->isEqual*/(node)) {
			point->setOffset(point->getOffset() + offset);
			break;
		}
	}
}