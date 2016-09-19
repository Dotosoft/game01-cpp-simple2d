#ifndef _MASKEDSPRITE_TILEDSPRITE_H_
#define _MASKEDSPRITE_TILEDSPRITE_H_

#include "Box2D\Box2D.h"
#include "cocos2d.h"

USING_NS_CC;

#define PTM_RATIO 32.f
// The number of outer circles (more, the smoother the circle)
#define NUM_SEGMENTS 12

typedef struct {
	GLfloat x;
	GLfloat y;
} Vertex2D;

static inline Vertex2D Vertex2DMake(GLfloat inX, GLfloat inY) {
	Vertex2D ret;
	ret.x = inX;
	ret.y = inY;
	return ret;
}

namespace squishybox2d {

	/**
	@brief    The cocos2d Application.

	The reason for implement as private inheritance is to hide some interface call by Director.
	*/
	class  MyNode : public cocos2d::Node
	{
		public:
			void createPhysicsObject(b2World* world);
	};
}

#endif // _MASKEDSPRITE_TILEDSPRITE_H_