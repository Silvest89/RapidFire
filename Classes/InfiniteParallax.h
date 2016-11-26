#ifndef __INFINITEPARALLAX__H__
#define __INFINITEPARALLAX__H__
#include "cocos2d.h"

USING_NS_CC;
class InfiniteParallax : public cocos2d::ParallaxNode
{
public:
	static cocos2d::Scene* createScene();
	InfiniteParallax();
	~InfiniteParallax();

	virtual bool init();

	CREATE_FUNC(InfiniteParallax);

	void update(float dt);
	cocos2d::Sprite *sprite1;
	cocos2d::Sprite *sprite2;
	//void incrementOffset(Point offset, Node* node);
	void incrementOffset(cocos2d::Point offset, cocos2d::Node * node);
};

class PointObject : public cocos2d::Ref
{
public:
	static PointObject * create(Point ratio, Point offset)
	{
		PointObject *ret = new PointObject();
		ret->initWithPoint(ratio, offset);
		ret->autorelease();
		return ret;
	}

	bool initWithPoint(Point ratio, Point offset)
	{
		_ratio = ratio;
		_offset = offset;
		_child = nullptr;
		return true;
	}

	inline const Point& getRatio() const { return _ratio; };
	inline void setRatio(const Point& ratio) { _ratio = ratio; };

	inline const Point& getOffset() const { return _offset; };
	inline void setOffset(const Point& offset) { _offset = offset; };

	inline Node* getChild() const { return _child; };
	inline void setChild(Node* child) { _child = child; };

private:
	Point _ratio;
	Point _offset;
	Node *_child; // weak ref
};
#endif