#ifndef _TEMPLATES_HELLOWORLD_SCENE_H_
#define _TEMPLATES_HELLOWORLD_SCENE_H_

#include "cocos2d.h"

namespace templates {

	class HelloWorld : public cocos2d::Layer
	{
		public:
			static cocos2d::Scene* createScene();

			virtual bool init();

			// a selector callback
			void menuCloseCallback(cocos2d::Ref* pSender);

			// implement the "static create()" method manually
			CREATE_FUNC(HelloWorld);
	};
}

#endif // _TEMPLATES_HELLOWORLD_SCENE_H_
