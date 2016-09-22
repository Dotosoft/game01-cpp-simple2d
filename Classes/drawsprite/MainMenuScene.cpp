#include "drawsprite\MainMenuScene.h"
#include "drawsprite\DrawSprite.h"

USING_NS_CC;
using namespace drawsprite;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	texture = Sprite::create("Default.png")->getTexture();

	// useDrawNode();

	auto winSize = Director::getInstance()->getWinSize();
	auto drawSprite = new DrawSprite();
	auto mySprite = drawSprite->createSprite05(winSize.width, winSize.height);
	mySprite->setAnchorPoint(Vec2(0.5, 0.5));
	mySprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(mySprite);

    return true;
}

void MainMenuScene::useDrawNode()
{
	auto drawNode = DrawNode::create();

	/* Rect */
	// void drawPolygon(Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor);
	Vec2 vertics[4] = { Vec2(0, 0), Vec2(200, 0), Vec2(200, 200), Vec2(0, 200) };
	drawNode->drawPolygon(vertics, 4, Color4F::GREEN, 10, Color4F::WHITE);

	/* Circle */
	// void drawDot(const Vec2 &pos, float radius, const Color4F &color);
	drawNode->drawDot(Vec2(200, 200), 50, Color4F::RED);

	/* Line */
	// void drawSegment(const Vec2 &from, const Vec2 &to, float radius, const Color4F &color);
	drawNode->drawSegment(Vec2(100, 400), Vec2(200, 400), 10, Color4F::ORANGE);
	this->addChild(drawNode, 1);
}

void MainMenuScene::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
	cocos2d::Director* director = cocos2d::Director::getInstance();
	director->pushMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	// deprecated
	/*kmGLPushMatrix();
	kmGLLoadMatrix(&transform);*/

	float selfHeight = this->getContentSize().height;
	float selfWidth = this->getContentSize().width;
	cocos2d::Point vertices[4] = { cocos2d::Point(10.f, 10.f), cocos2d::Point(10.f, selfHeight - 10), cocos2d::Point(selfWidth - 10, selfHeight - 10), cocos2d::Point(selfWidth - 10, 10.f) };
	cocos2d::DrawPrimitives::drawSolidPoly(vertices, 4, Color4F(0, 1, 0, 1));

	//add your primitive drawing code here
	cocos2d::DrawPrimitives::drawLine(Vec2(0, 0), Vec2(100, 100));
}

//void MainMenuScene::onDrawPolygon(const cocos2d::Mat4 &transform, uint32_t flags) {
//	//kmGLPushMatrix();
//	//kmGLLoadMatrix(&transform);
//
//	//draw
//	if (areaTrianglePointCount <= 1)
//		return;
//
//	CC_NODE_DRAW_SETUP();
//
//
//	cocos2d::GL::bindTexture2D(texture->getName());
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//	GL::blendFunc(blendFunc.src, blendFunc.dst);
//
//	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
//
//	if (sizeof(Point) == sizeof(Vec2)) {
//
//		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, areaTrianglePoints);
//		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
//		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)areaTrianglePointCount);
//
//	}
//	else {
//		Vec2* newAreaTrianglePoints = new Vec2[areaTrianglePointCount];
//		Vec2* newTextureCoordinates = new Vec2[areaTrianglePointCount];
//
//		if (newAreaTrianglePoints != NULL && newTextureCoordinates != NULL) {
//
//			for (unsigned int i = 0; i < areaTrianglePointCount; i++) {
//				newTextureCoordinates[i].x = textureCoordinates[i].x;
//				newTextureCoordinates[i].y = textureCoordinates[i].y;
//
//				newAreaTrianglePoints[i].x = areaTrianglePoints[i].x;
//				newAreaTrianglePoints[i].y = areaTrianglePoints[i].y;
//			}
//			glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, newAreaTrianglePoints);
//			glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, newTextureCoordinates);
//			//glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)areaTrianglePointCount);
//
//			short indices1[] = { 0, 1, 2 };
//			short indices2[] = { 3, 4, 5 };
//			glDrawElements(GL_TRIANGLES, 3, GL_SHORT, indices1);
//			glDrawElements(GL_TRIANGLES, 3, GL_SHORT, indices2);
//
//
//
//			CC_SAFE_DELETE_ARRAY(newAreaTrianglePoints);
//			CC_SAFE_DELETE_ARRAY(newTextureCoordinates);
//		}
//	}
//
//	CC_INCREMENT_GL_DRAWS(1);
//}