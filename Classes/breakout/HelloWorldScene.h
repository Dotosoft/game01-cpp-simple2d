#ifndef _BREAKOUT_HELLOWORLD_SCENE_H_
#define _BREAKOUT_HELLOWORLD_SCENE_H_

#define PTM_RATIO 32.0

#include "cocos2d.h"
#include <Box2D/Box2D.h>

USING_NS_CC;

namespace breakout {

	class HelloWorld : public cocos2d::Layer
	{
		public:
			static cocos2d::Scene* createScene();

			virtual bool init();

			// a selector callback
			void menuCloseCallback(cocos2d::Ref* pSender);

			// implement the "static create()" method manually
			CREATE_FUNC(HelloWorld);

			void tick(float dt);
		private:
			b2World *_world;
			b2Body *_groundBody;
			b2Fixture *_bottomFixture;
			b2Fixture *_ballFixture;
	};
}

#endif // _BREAKOUT_HELLOWORLD_SCENE_H_
