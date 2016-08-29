#ifndef _MASKEDSPRITE_TILEDSPRITE_H_
#define _MASKEDSPRITE_TILEDSPRITE_H_

#include "cocos2d.h"

USING_NS_CC;

namespace maskedsprite {

	/**
	@brief    The cocos2d Application.

	The reason for implement as private inheritance is to hide some interface call by Director.
	*/
	class  MaskedSprite : public cocos2d::Node
	{
		private:
			CCTexture2D * _maskTexture;
			GLuint _textureLocation;
			GLuint _maskLocation;
		public:
			static Sprite * initWithSprite(Sprite* sprite, Sprite* maskSprite);
			static Sprite * initWithSprite(Sprite* sprite, const char * maskFile);
			static Sprite * initWithSpriteFrame(SpriteFrame * spriteFrame, const char * maskFile);
			static Sprite * initWithFile(const char * file, const char * maskFile);
			static Sprite * initWithFile(const char * file, SpriteFrame * mask);
	};
}

#endif // _MASKEDSPRITE_TILEDSPRITE_H_