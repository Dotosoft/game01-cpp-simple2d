#ifndef _FLAPPY_BIRD_H_
#define _FLAPPY_BIRD_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

namespace flappy {

	class Bird
	{
		public:
			Bird( cocos2d::Layer *layer );

			void Fall( );
			void Fly( )
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("flappy/Sounds/Wing.mp3");
				isFalling = false;
			};

			void StopFlying( ) { isFalling = true; }

		private:
			cocos2d::Size visibleSize;
			cocos2d::Vec2 origin;

			cocos2d::Sprite *flappyBird;

			bool isFalling;

	};

}

#endif // _FLAPPY_BIRD_H_
