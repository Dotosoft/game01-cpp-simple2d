#ifndef _FLAPPY_PIPE_H_
#define _FLAPPY_PIPE_H_

#include "cocos2d.h"

namespace flappy {

	class Pipe
	{
		public:
			Pipe();

			void SpawnPipe( cocos2d::Layer *layer );

		private:
			cocos2d::Size visibleSize;
			cocos2d::Vec2 origin;

	};

}

#endif // _FLAPPY_PIPE_H_
