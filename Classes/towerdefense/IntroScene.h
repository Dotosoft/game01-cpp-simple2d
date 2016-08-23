#ifndef _TOWERDEFENSE_INTRO_SCENE_H_
#define _TOWERDEFENSE_INTRO_SCENE_H_

#include "cocos2d.h"

namespace towerdefense {

	class Intro : public cocos2d::LayerColor
	{
		public:
			static cocos2d::Scene* createScene();

			virtual bool init();

			// a selector callback
			void menuCloseCallback(cocos2d::Ref* pSender);

			// implement the "static create()" method manually
			CREATE_FUNC(Intro);

			virtual void onEnter();

		private:

	};

}

#endif // _TOWERDEFENSE_INTRO_SCENE_H_
