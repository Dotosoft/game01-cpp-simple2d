#ifndef _MASKEDSPRITE_TILEDSPRITE_H_
#define _MASKEDSPRITE_TILEDSPRITE_H_

#include "cocos2d.h"

USING_NS_CC;

namespace maskedsprite {

	/**
	@brief    The cocos2d Application.

	The reason for implement as private inheritance is to hide some interface call by Director.
	*/
	class  MaskedSprite : public cocos2d::Sprite
	{
		public:
			static MaskedSprite * createWithSprite(Sprite*, std::string);
			static MaskedSprite * createWithSprite(Sprite*, Sprite*);
			static MaskedSprite * createWithFile(std::string, Sprite*);
			static MaskedSprite * createWithFile(std::string, std::string);
			// virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
			// virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

		private:
			CC_SYNTHESIZE(Texture2D *, _maskTexture, MaskTexture);
			CC_SYNTHESIZE(GLuint, _textureLocation, TextureLocation);
			CC_SYNTHESIZE(GLuint, _maskLocation, MaskLocation);
	};
}

#endif // _MASKEDSPRITE_TILEDSPRITE_H_