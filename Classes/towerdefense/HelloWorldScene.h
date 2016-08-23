#ifndef _TOWERDEFENSE_HELLOWORLD_SCENE_H_
#define _TOWERDEFENSE_HELLOWORLD_SCENE_H_

#include "towerdefense/Tower.h"
#include "towerdefense/Waypoint.h"
#include "towerdefense/Enemy.h"
#include "cocos2d.h"

namespace towerdefense {

	class Tower;
	class Enemy;
	class Waypoint;

	class HelloWorld : public cocos2d::LayerColor
	{
		cocos2d::Vector<cocos2d::Sprite *> _towerBases;
		cocos2d::Vector<Tower *> _towers;
		cocos2d::Vector<Waypoint *> _waypoints;
		cocos2d::Vector<Enemy *> _enemies;

		float _scaleY;
		float _scaleX;
		float radiusTwo;
		int wave;
		Label *ui_wave_lbl;

		// Health Player
		int playerHp;
		bool gameEnded;
		Label *ui_hp_lbl;

		// Gold Player
		int playerGold;
		Label *ui_gold_lbl;

		public:
			static cocos2d::Scene* createScene();

			virtual bool init();

			// a selector callback
			void menuCloseCallback(cocos2d::Ref* pSender);

			// implement the "static create()" method manually
			CREATE_FUNC(HelloWorld);
			void loadTowerPositions();
			void addWaypoints();
			bool loadWave();

			// Add Enemy
			bool circle( Vec2 circlePoint, float radius, Vec2 circlePointTwo, float radiusTwo );
			void ccFillPoly(Vec2 *poli, int points, bool closePolygon);
			void enemyGotKilled();
			void getHpDamage();

			// Gold
			void awardGold(int gold);

			float getScaleX() const {
				return _scaleX;
			}

			float getScaleY() const {
				return _scaleY;
			}

			cocos2d::Vector<Enemy *> & getEnemies() {
				return  _enemies;
			}

			cocos2d::Vector<Waypoint *> & getWaypoints() {
				return _waypoints;
			}

			cocos2d::Vector<Tower *> & getTowers() {
				return _towers;
			}

		private:
			void doGameOver();
			bool canBuyTower();
			virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	};

}

#endif // _TOWERDEFENSE_HELLOWORLD_SCENE_H_
