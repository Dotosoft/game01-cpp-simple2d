#ifndef _SPACESHOOTER_MAINMENU_SCENE_H_
#define _SPACESHOOTER_MAINMENU_SCENE_H_

#include "cocos2d.h"

namespace spaceshooter {

	class MainMenu : public cocos2d::Layer
	{
		public:
			static cocos2d::Scene* createScene();
			virtual bool init();

			// implement the "static create()" method manually
			CREATE_FUNC(MainMenu);

			void GoToGameScene(Ref *pSender);

			void onAcceleration(cocos2d::Acceleration *acc, cocos2d::Event *event);
	};

}

#endif // _SPACESHOOTER_MAINMENU_SCENE_H_
