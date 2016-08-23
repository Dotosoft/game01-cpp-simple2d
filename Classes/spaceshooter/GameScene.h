#ifndef _SPACESHOOTER_GAMESCREEN_SCENE_H_
#define _SPACESHOOTER_GAMESCREEN_SCENE_H_

#include "cocos2d.h"

namespace spaceshooter {

	class GameScreen : public cocos2d::Layer
	{
		public:
			static cocos2d::Scene* createScene();
			virtual bool init();

			// implement the "static create()" method manually
			CREATE_FUNC(GameScreen);

			void GoToPauseScene(Ref *pSender);
			void GoToGameOverScene(Ref *pSender);

			void update(float dt);
			cocos2d::Sprite *backgroundSpriteArray[2];

			void spawnAsteroid(float dt);
			std::vector<cocos2d::Sprite *> asteroids;

			cocos2d::Sprite *playerSprite;

			bool onTouchBegan(cocos2d::Touch *touch, cocos2d:: Event * event);
			void onTouchMoved(cocos2d::Touch *touch, cocos2d:: Event * event);
			void onTouchEnded(cocos2d::Touch *touch, cocos2d:: Event * event);
			void onTouchCancelled(cocos2d::Touch *touch, cocos2d:: Event * event);

			bool isTouching;
			float touchPosition;

			void setPhysicsWorld(cocos2d::PhysicsWorld* world) {
				mWorld = world;
				mWorld->setGravity(cocos2d::Vect(0, 0));
			}
			bool onContactBegin(cocos2d::PhysicsContact& contact);
			cocos2d::PhysicsWorld* mWorld;
	};

}

#endif // _SPACESHOOTER_GAMESCREEN_SCENE_H_
