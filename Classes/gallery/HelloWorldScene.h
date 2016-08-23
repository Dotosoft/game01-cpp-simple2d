#ifndef _GALLERY_HELLOWORLD_SCENE_H_
#define _GALLERY_HELLOWORLD_SCENE_H_

#include "cocos2d.h"

namespace gallery {

	class HelloWorld : public cocos2d::Layer
	{
		public:
			unsigned int currImageIndex;
			static cocos2d::Scene* createScene();
			cocos2d::Scene* scene(unsigned int i_index);
			virtual bool init();
			virtual void onEnter();
			void displayImage(Layer *myLayer);
			CREATE_FUNC(HelloWorld);
		private :
			cocos2d::Point pointStartPos, pointEndPos;
			std::vector<std::string> myImages = {
				"gallery/image001.png",
				"gallery/image002.png",
				"gallery/image003.png"
			};
	};
}

#endif // _GALLERY_HELLOWORLD_SCENE_H_
