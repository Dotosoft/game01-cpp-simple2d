#ifndef _TOWERDEFENSE_TOWER_H_
#define _TOWERDEFENSE_TOWER_H_

#include "towerdefense/HelloWorldScene.h"
#include "towerdefense/Enemy.h"
#include "cocos2d.h"

#define kTOWER_COST 300

USING_NS_CC;

namespace towerdefense {

	class HelloWorld;
	class Enemy;

	class Tower : public cocos2d::Node
	{
		int attackRange;
		int damage;
		float fireRate;

		HelloWorld* theGame;
		Sprite* mySprite;

		// Attack Property
		bool attacking;
		Enemy *chosenEnemy;

		public:
			void targetKilled();
			static Tower* nodeWithTheGame(HelloWorld *game, Vec2 location);
		private:
			// Logic Looping
			void update(float dt);

			void attackEnemy();
			void chosenEnemyForAttack(Enemy *enemy);
			void shootWeapon(float ccTime);
			void removeBullet(Sprite *bullet);
			void damageEnemy();
			void lostSightOfEnemy();

			// Draw Canvas
			CustomCommand _customCommand;
			virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
			virtual void onDraw();
	};

}

#endif // _TOWERDEFENSE_TOWER_H__
