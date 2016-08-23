/*
 * Enemy.h
 *
 *  Created on: Jul 5, 2016
 *      Author: denis
 */

#ifndef _TOWERDEFENSE_ENEMY_H_
#define _TOWERDEFENSE_ENEMY_H_

#include "towerdefense/Waypoint.h"
#include "towerdefense/HelloWorldScene.h"
#include "towerdefense/Tower.h"
#include "cocos2d.h"

USING_NS_CC;

namespace towerdefense {

	class Waypoint;
	class HelloWorld;
	class Tower;

	class Enemy : public Node {

		Vec2 myPosition;
		int maxHp;
		int currentHp;
		float walkingSpeed;
		Waypoint *destinationWaypoint;
		bool active;
		HelloWorld *theGame;
		Sprite *mySprite;

		public:
			static Enemy* nodeWithTheGame(HelloWorld *_game);
			void doActivate(float ccTime);
			void getRemoved();

			Sprite *getMySprite() const {
				return mySprite;
			}

			// Attack Method
			void getAttacked(Tower *attacker);
			void getLoseSight(Tower *attacker);
			void getDamaged(int damage);

		private:
			Vector<Tower *> attackedBy;

			CustomCommand _customCommand;
			virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
			virtual void onDraw();

			void update(float ccTime);

	};

}

#endif /* TOWERDEFENSE_ENEMY_H_ */
