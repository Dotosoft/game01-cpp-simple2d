#ifndef _SPACESHOOTER_GAMEOVER_SCENE_H_
#define _SPACESHOOTER_GAMEOVER_SCENE_H_

#include "cocos2d.h"

namespace spaceshooter {

	class GameOver : public cocos2d::Layer
	{
		public:
			static cocos2d::Scene* createScene();
			virtual bool init();

			// implement the "static create()" method manually
			CREATE_FUNC(GameOver);

			void GoToGameScene(Ref *pSender);
			void GoToMainMenuScene(Ref *pSender);
	};

}

#endif // _SPACESHOOTER_GAMEOVER_SCENE_H_
