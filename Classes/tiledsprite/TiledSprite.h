//
// Cocos2d Tiled Sprite
//
// Ebyan Alvarez-Buylla
// http://www.nolithius.com
//
// Creates a tiled sprite from the source sprite's texture, tiling it or clipping it to the desired width and height.
// Usage: [[TiledSprite alloc] initWithSprite:spriteWithTextureOrSubtexture width:640 height:480];
//
// Further details and screenshot at:
// http://www.nolithius.com/game-development/cocos2d-iphone-repeating-sprite
//
// License: Public Domain. Enjoy!
//

#ifndef _TILEDSPRITE_TILEDSPRITE_H_
#define _TILEDSPRITE_TILEDSPRITE_H_

#include "cocos2d.h"

USING_NS_CC;

namespace tiledsprite {

	/**
	@brief    The cocos2d Application.

	The reason for implement as private inheritance is to hide some interface call by Director.
	*/
	class  TiledSprite : public cocos2d::Node
	{
		private:
			int width;
			int height;
		public:
			TiledSprite(Sprite* p_sprite, int p_width, int p_height);
	};
}

#endif // _TILEDSPRITE_TILEDSPRITE_H_