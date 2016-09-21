#ifndef _DRAWSPRITE_MAIN_MENU_SCENE_H_
#define _DRAWSPRITE_MAIN_MENU_SCENE_H_

#include "cocos2d.h"
#include "GameResources.h"

USING_NS_CC;

namespace drawsprite {

	class MainMenuScene : public cocos2d::Layer
	{
		public:
			// there's no 'id' in cpp, so we recommend returning the class instance pointer
			static cocos2d::Scene* createScene();

			// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
			virtual bool init();

			// implement the "static create()" method manually
			CREATE_FUNC(MainMenuScene);

			void useDrawNode();
			// void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
			// Sprite* spriteWithColor(Color4F bgColor, float textureWidth, float textureHeight);
			Sprite* spriteWithColorCustom(Color4F bgColor, float textureWidth, float textureHeight);
			void onDrawSprite();

		private:
			CustomCommand _customCmd;
			/* virtual	void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags) {
				cocos2d::Layer::draw(renderer, transform, flags);

				_customCmd.init(_globalZOrder);
				_customCmd.func = CC_CALLBACK_0(MainMenuScene::onDraw, this, transform, flags);
				renderer->addCommand(&_customCmd);
			} */
	};

}

#endif // _DRAWSPRITE_MAIN_MENU_SCENE_H_