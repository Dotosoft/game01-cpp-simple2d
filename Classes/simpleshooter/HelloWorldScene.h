#ifndef _SIMPLESHOOTER_HELLOWORLD_SCENE_H_
#define _SIMPLESHOOTER_HELLOWORLD_SCENE_H_

#include "simpleshooter/Monster.h"
#include "cocos2d.h"

namespace simpleshooter {

	class HelloWorld : public cocos2d::LayerColor
	{
		public:
			static cocos2d::Scene* createScene();

			virtual bool init();

			// a selector callback
			void menuCloseCallback(cocos2d::Ref* pSender);

			// implement the "static create()" method manually
			CREATE_FUNC(HelloWorld);

			void addMonster();

			// void onTouchEnd( cocos2d::Touch *touch, cocos2d::Event *event );
			virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
			virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);

		private:

			void gameLogic(float dt);
			void update(float dt);

			cocos2d::Sprite *_player;
			cocos2d::Sprite *_nextProjectile;

			cocos2d::Vector<Monster *> _monsters;
			cocos2d::Vector<cocos2d::Node *> _projectiles;

			int _monstersDestroyed;
	};
}

#endif // _SIMPLESHOOTER_HELLOWORLD_SCENE_H_
