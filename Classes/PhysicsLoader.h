
#ifndef PhysicsLoader_x_h
#define PhysicsLoader_x_h

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class BodyDef;
class b2Body;

class PhysicsLoader 
{
public:
    PhysicsLoader();
    void addShapesWithFile(const std::string &plist);
	void addShapesWithJSON(const std::string &plist, b2FixtureDef &data);
    void addFixturesToBody(b2Body *body, const std::string &shape);
    Vec2 getAnchorPointForShape(const std::string &shape) const;
    void reset();
    float getPtmRatio() const;
    ~PhysicsLoader();
	std::map<std::string, BodyDef*>         m_shapeObjects;
        
private:
    //std::map<std::string, BodyDef*>         m_shapeObjects;
    float                                   m_ptmRatio;
};


#endif
