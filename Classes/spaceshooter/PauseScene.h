#ifndef _SPACESHOOTER_PAUSEMENU_SCENE_H_
#define _SPACESHOOTER_PAUSEMENU_SCENE_H_

#include "cocos2d.h"

namespace spaceshooter {

	class PauseMenu : public cocos2d::Layer
	{
		public:
			static cocos2d::Scene* createScene();
			virtual bool init();

			// implement the "static create()" method manually
			CREATE_FUNC(PauseMenu);

			void Resume(Ref *pSender);
			void GoToMainMenuScene(Ref *pSender);
			void Retry(Ref *pSender);
	};

}

#endif // _SPACESHOOTER_PAUSEMENU_SCENE_H_
