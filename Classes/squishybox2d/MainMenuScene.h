#ifndef _SQUISHYBOX2D_MAIN_MENU_SCENE_H_
#define _SQUISHYBOX2D_MAIN_MENU_SCENE_H_

#include "cocos2d.h"
#include "GameResources.h"
#include "Box2D\Box2D.h"

USING_NS_CC;

namespace squishybox2d {

	class MainMenuScene : public cocos2d::Layer
	{
		b2World* world;
		/// GLESDebugDraw *m_debugDraw;

		public:
			// there's no 'id' in cpp, so we recommend returning the class instance pointer
			static cocos2d::Scene* createScene();

			// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
			virtual bool init();

			// implement the "static create()" method manually
			CREATE_FUNC(MainMenuScene);

	};

}

#endif // _SQUISHYBOX2D_MAIN_MENU_SCENE_H_