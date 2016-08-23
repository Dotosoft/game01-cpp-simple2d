#include "towerdefense/HelloWorldScene.h"
#include "towerdefense/Waypoint.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace towerdefense;

Waypoint* Waypoint::nodeWithTheGame(HelloWorld *game, Vec2 location, Waypoint *next)
{
	Waypoint* waypoint = new Waypoint();
	if(!waypoint->init()) {
		return waypoint;
	}

	waypoint->nextWaypoint = next;
	waypoint->theGame = game;
	waypoint->setPosition(Vec2::ZERO);
	waypoint->myPosition = location;
	waypoint->theGame->addChild( waypoint );

	return waypoint;
}

void Waypoint::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder+10);
	_customCommand.func = CC_CALLBACK_0(Waypoint::onDraw, this);
	renderer->addCommand(&_customCommand);
}

void Waypoint::onDraw()
{
	cocos2d::DrawPrimitives::setDrawColor4B( 0, 255, 2, 255 );
	cocos2d::DrawPrimitives::drawCircle(this->getMyPosition(), 6, 360, 30, false);
	cocos2d::DrawPrimitives::drawCircle(this->getMyPosition(), 2, 360, 30, false);

	if(this->nextWaypoint) {
		cocos2d::DrawPrimitives::drawLine(this->getMyPosition(), this->nextWaypoint->getMyPosition());
	}
}
