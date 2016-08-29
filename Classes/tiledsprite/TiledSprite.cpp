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

#include "tiledsprite\TiledSprite.h"

using namespace tiledsprite;

TiledSprite::TiledSprite(Sprite * p_sprite, int p_width, int p_height)
{
	// Only bother doing anything if the sizes are positive
	if (p_width > 0 && p_height > 0)
	{
		auto spriteBounds = p_sprite->getTextureRect();
		int sourceX = spriteBounds.origin.x;
		int sourceY = spriteBounds.origin.y;
		int sourceWidth = spriteBounds.size.width;
		int sourceHeight = spriteBounds.size.height;
		auto texture = p_sprite->getTexture();

		// Case 1: both width and height are smaller than source sprite, just clip
		if (p_width <= sourceWidth && p_height <= sourceHeight)
		{
			auto sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY + sourceHeight - p_height, p_width, p_height));
			sprite->setAnchorPoint(Vec2::ZERO);
			this->addChild(sprite);
		}
		// Case 2: only width is larger than source sprite
		else if (p_width > sourceWidth && p_height <= sourceHeight)
		{
			// Stamp sideways until we can
			int ix = 0;
			while (ix < p_width - sourceWidth)
			{
				auto sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY + sourceHeight - p_height, sourceWidth, p_height));
				sprite->setAnchorPoint(Vec2::ZERO);
				sprite->setPosition(Vec2(ix, 0));
				this->addChild(sprite);

				ix += sourceWidth;
			}

			// Stamp the last one
			auto sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY + sourceHeight - p_height, p_width - ix, p_height));
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(ix, 0));
			this->addChild(sprite);
		}
		// Case 3: only height is larger than source sprite
		else if (p_height >= sourceHeight && p_width <= sourceWidth)
		{
			// Stamp down until we can
			int iy = 0;
			while (iy < p_height - sourceHeight)
			{
				auto sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY, p_width, sourceHeight));
				sprite->setAnchorPoint(Vec2::ZERO);
				sprite->setPosition(Vec2(0, iy));
				this->addChild(sprite);

				iy += sourceHeight;
			}

			// Stamp the last one
			int remainingHeight = p_height - iy;
			auto sprite = Sprite::createWithTexture(texture, Rect(sourceX, sourceY + sourceHeight - remainingHeight, p_width, remainingHeight));
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, iy));
			this->addChild(sprite);
		}
		// Case 4: both width and height are larger than source sprite (Composite together several Case 2's, as needed)
		else
		{
			// Stamp down until we can
			int iy = 0;
			while (iy < p_height - sourceHeight) {

				auto sprite = new TiledSprite(p_sprite, p_width, sourceHeight);
				sprite->setAnchorPoint(Vec2::ZERO);
				sprite->setPosition(Vec2(0, iy));
				this->addChild(sprite);

				iy += sourceHeight;
			}

			// Stamp the last one
			auto sprite = new TiledSprite(p_sprite, width, p_height - iy);
			sprite->setAnchorPoint(Vec2::ZERO);
			sprite->setPosition(Vec2(0, iy));
			this->addChild(sprite);
		}
	}
}

Sprite * TiledSprite::createWithImage(Image * img, int p_width, int p_height)
{
	// auto sprite = Sprite::create(RESOURCES_TILED_IMAGE_BRICK);
	auto texture = new Texture2D();
	texture->initWithImage(img);

	// Method 1
	Texture2D::TexParams params;
	params.minFilter = GL_LINEAR;
	params.magFilter = GL_LINEAR;
	params.wrapS = GL_REPEAT;
	params.wrapT = GL_REPEAT;
	// Method 2
	// Texture2D::TexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };

	auto sprite = Sprite::createWithTexture(texture, Rect(0, 0, p_width, p_height));
	sprite->getTexture()->setTexParameters(params);

	return sprite;
}
