#ifndef _DRAWSPRITE_DRAWSPRITE_H_
#define _DRAWSPRITE_DRAWSPRITE_H_

#include "cocos2d.h"
#include "GameResources.h"
#include "GameGlobals.h"

USING_NS_CC;

#define NUM_VERTEX 13

namespace drawsprite {

	class DrawSprite : public cocos2d::Layer
	{
		typedef struct {
			GLfloat x;
			GLfloat y;
		} Vertex2D;

		Vertex2D triangleStripPos[13];
		Vertex2D textCoords[13];

		public:
			Sprite* createSprite01(cocos2d::Color4F bgColor, float textureWidth, float textureHeight);
			Sprite* createSprite02(cocos2d::Color4F bgColor, float textureWidth, float textureHeight); // Not Working
			Sprite* createSprite03(cocos2d::Color4F bgColor, float textureWidth, float textureHeight);
			Sprite* createSprite04(cocos2d::Color4F bgColor, float textureWidth, float textureHeight);
			Sprite* createSprite05(float textureWidth, float textureHeight);

		private:
			CustomCommand _customCmd;
			Texture2D *texture;
			// Sprite* noise;

			void onDrawSprite03();
			void onDrawSprite04();
			void onDrawSprite05(EStripeType stripe_type, int num_stripes);
			void RenderStripes(EStripeType stripe_type, int num_stripes);
			void RenderGradient();
			void RenderHighlight();
			void RenderTopBorder();
			void RenderNoise();
	};

}

#endif // _DRAWSPRITE_DRAWSPRITE_H_