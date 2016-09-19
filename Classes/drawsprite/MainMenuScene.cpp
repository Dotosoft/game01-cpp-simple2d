#include "drawsprite\MainMenuScene.h"

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

	// useDrawNode();

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