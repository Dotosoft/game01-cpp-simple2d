/*
 * Waypoint.h
 *
 *  Created on: Jul 4, 2016
 *      Author: denis
 */

#ifndef _TOWERDEFENSE_WAYPOINT_H_
#define _TOWERDEFENSE_WAYPOINT_H_

#include "towerdefense/HelloWorldScene.h"
#include "cocos2d.h"
USING_NS_CC;

namespace towerdefense {

	class HelloWorld;

	class Waypoint : public cocos2d::Node {

		HelloWorld *theGame;
		Vec2 myPosition;
		Waypoint *nextWaypoint;

		public:
			static Waypoint* nodeWithTheGame(HelloWorld *game, Vec2 location, Waypoint *nextWaypoint);
			Vec2 getMyPosition() const {
				return myPosition;
			}

			Waypoint* getNextWaypoint() const {
				return nextWaypoint;
			}

		private:
			CustomCommand _customCommand;
			virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
			virtual void onDraw();
	};

}

#endif /* _TOWERDEFENSE_WAYPOINT_H_ */
