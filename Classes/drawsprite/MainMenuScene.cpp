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

	auto winSize = Director::getInstance()->getWinSize();

	// useDrawNode();

	auto mySprite = spriteWithColorCustom(Color4F::GREEN, winSize.width, winSize.height);
	mySprite->setAnchorPoint(Vec2(0.5, 0.5));
	mySprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(mySprite);

    return true;
}

//Sprite* MainMenuScene::spriteWithColor(cocos2d::Color4F bgColor, float textureWidth, float textureHeight)
//{
//	RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);
//	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
//	rt->end();
//	return Sprite::createWithTexture(rt->getSprite()->getTexture());
//}

Sprite* MainMenuScene::spriteWithColorCustom(cocos2d::Color4F bgColor, float textureWidth, float textureHeight)
{
	//RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);
	//rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	// this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));

	//CC_NODE_DRAW_SETUP();

	//// 3: Draw into the texture
	//float gradientAlpha = 0.7f;
	//CCPoint vertices[4];
	//ccColor4F colors[4];
	//int nVertices = 0;

	//vertices[nVertices] = Point(0, 0);
	//colors[nVertices++] = Color4F(0, 0, 0, 0);
	//vertices[nVertices] = Point(textureWidth, 0);
	//colors[nVertices++] = Color4F(0, 0, 0, 0);
	//vertices[nVertices] = Point(0, textureHeight);
	//colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);
	//vertices[nVertices] = Point(textureWidth, textureHeight);
	//colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);

	//ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);

	//glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	//glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
	//glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
	//rt->end();
	//return Sprite::createWithTexture(rt->getSprite()->getTexture());


	RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);
	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	//CustomCommand _customCmd;
	_customCmd.init(rt->getGlobalZOrder());
	_customCmd.func = CC_CALLBACK_0(MainMenuScene::onDrawSprite, this);
	auto renderer = Director::getInstance()->getRenderer();
	renderer->addCommand(&_customCmd);
	rt->end();
	return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

void MainMenuScene::onDrawSprite()
{
	CCLOG("MainMenuScene::onDrawSprite");
	this->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
	this->getShaderProgram()->use();
	this->getShaderProgram()->setUniformsForBuiltins();

	// Size winSize = Director::getInstance()->getVisibleSize();
	float gradientAlpha = 0.7;
	Vertex2F vertices[4];
	Color4F colors[4];
	int nVertices = 0;
	float width = 512;
	vertices[nVertices] = { 0, 0 };
	colors[nVertices++] = { 0, 0, 0, 0 };
	vertices[nVertices] = { width, 0 };
	colors[nVertices++] = { 0, 0, 0, 0 };
	vertices[nVertices] = { 0, width };
	colors[nVertices++] = { 0, 0, 0, gradientAlpha };
	vertices[nVertices] = { 2, width };
	colors[nVertices++] = { 0, 0, 0, gradientAlpha };

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_COLOR | GL::VERTEX_ATTRIB_FLAG_POSITION);

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
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

//void MainMenuScene::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
//{
//	cocos2d::Director* director = cocos2d::Director::getInstance();
//	director->pushMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
//	director->loadMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
//
//	// deprecated
//	/*kmGLPushMatrix();
//	kmGLLoadMatrix(&transform);*/
//
//	float selfHeight = this->getContentSize().height;
//	float selfWidth = this->getContentSize().width;
//	cocos2d::Point vertices[4] = { cocos2d::Point(10.f, 10.f), cocos2d::Point(10.f, selfHeight - 10), cocos2d::Point(selfWidth - 10, selfHeight - 10), cocos2d::Point(selfWidth - 10, 10.f) };
//	cocos2d::DrawPrimitives::drawSolidPoly(vertices, 4, Color4F(0, 1, 0, 1));
//
//	//add your primitive drawing code here
//	cocos2d::DrawPrimitives::drawLine(Vec2(0, 0), Vec2(100, 100));
//}