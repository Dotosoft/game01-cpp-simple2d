#ifndef __FREEHAND_HELLO_WORLD_H__
#define __FREEHAND_HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

namespace freehand {

	class PhysicsSprite : public cocos2d::Sprite
	{
		public:
			PhysicsSprite();
			void setPhysicsBody(b2Body * body);
			virtual bool isDirty(void);
			virtual cocos2d::AffineTransform nodeToParentTransform(void);
		private:
			b2Body* m_pBody;    // strong ref
			Point m_obAnchorPointInPoints;
			AffineTransform m_sTransform;
	};

	class HelloWorld : public cocos2d::Layer {
		public:
			~HelloWorld();
			HelloWorld();

			// returns a Scene that contains the HelloWorld as the only child
			static cocos2d::Scene* createScene();

			void initPhysics();
			// adds a new sprite at a given coordinate
			void addNewSpriteAtPosition(cocos2d::Point p);

			// Draw Canvas
//			CustomCommand _customCommand;
//			virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);
//			virtual void onDraw();

			bool onTouchBegan( const std::vector<Touch*>& touches, Event* events );
			void onTouchMoved( const std::vector<Touch*>& touches, Event* events );
			void onTouchEnded( const std::vector<Touch*>& touches, Event* events );

			void update(float dt);

			void addRectangleBetweenPointsToBody(b2Body* body, cocos2d::Point start, cocos2d::Point end);
			cocos2d::Rect getBodyRectangle(b2Body* body);

		private:
			b2World* world;
			cocos2d::Texture2D* m_pSpriteTexture; // weak ref

			cocos2d::RenderTexture *target;
			cocos2d::Sprite *brush;

			//GLESDebugDraw* debugDraw;
			cocos2d::Point previousLocation;
			b2Body* currentPlatformBody;

			std::vector<cocos2d::Point> plataformPoints;
	};

}

#endif // __HELLO_WORLD_H__
