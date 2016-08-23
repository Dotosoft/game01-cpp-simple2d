#ifndef _SIMPLESHOOTER_GAMEOVER_SCENE_H_
#define _SIMPLESHOOTER_GAMEOVER_SCENE_H_

#include "cocos2d.h"

namespace simpleshooter {

	class GameOver : public cocos2d::LayerColor
	{
		public:
			// static cocos2d::Scene* createScene();
			static cocos2d::Scene* createSceneWithWon(bool won);

			virtual bool init();
			void setWon(bool won);

			// implement the "static create()" method manually
			CREATE_FUNC(GameOver);

	};
}

#endif // _SIMPLESHOOTER_GAMEOVER_SCENE_H_
