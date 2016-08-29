#ifndef _MASKEDSPRITE_MAIN_MENU_SCENE_H_
#define _MASKEDSPRITE_MAIN_MENU_SCENE_H_

#include "cocos2d.h"
#include "maskedsprite\MaskedSprite.h"
#include "GameResources.h"

USING_NS_CC;

namespace maskedsprite {

	class MainMenuScene : public cocos2d::Layer
	{

		private:
			Sprite * demoSprite;
			Sprite * normalSprite;
			Sprite * overlaySprite;

		public:
			// there's no 'id' in cpp, so we recommend returning the class instance pointer
			static cocos2d::Scene* createScene();

			// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
			virtual bool init();

			// implement the "static create()" method manually
			CREATE_FUNC(MainMenuScene);

	};

}

#endif // _MASKEDSPRITE_MAIN_MENU_SCENE_H_