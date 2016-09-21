#include "drawsprite\DrawSprite.h"

USING_NS_CC;
using namespace drawsprite;

Sprite* DrawSprite::createSprite01(cocos2d::Color4F bgColor, float textureWidth, float textureHeight) {
	RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);
	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	rt->end();
	return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

Sprite* DrawSprite::createSprite02(cocos2d::Color4F bgColor, float textureWidth, float textureHeight) {
	RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);
	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	// this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	this->setShaderProgram(ShaderCache::getInstance()->getProgram(GLProgram::SHADER_NAME_POSITION_COLOR));

	CC_NODE_DRAW_SETUP();

	// 3: Draw into the texture
	float gradientAlpha = 0.7f;
	CCPoint vertices[4];
	ccColor4F colors[4];
	int nVertices = 0;

	vertices[nVertices] = Point(0, 0);
	colors[nVertices++] = Color4F(0, 0, 0, 0);
	vertices[nVertices] = Point(textureWidth, 0);
	colors[nVertices++] = Color4F(0, 0, 0, 0);
	vertices[nVertices] = Point(0, textureHeight);
	colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);
	vertices[nVertices] = Point(textureWidth, textureHeight);
	colors[nVertices++] = Color4F(0, 0, 0, gradientAlpha);

	// ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_COLOR | GL::VERTEX_ATTRIB_FLAG_POSITION);

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
	rt->end();
	return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

Sprite* DrawSprite::createSprite03(cocos2d::Color4F bgColor, float textureWidth, float textureHeight) {
	RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);
	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	//CustomCommand _customCmd;
	_customCmd.init(rt->getGlobalZOrder());
	_customCmd.func = CC_CALLBACK_0(DrawSprite::onDrawSprite03, this);
	auto renderer = Director::getInstance()->getRenderer();
	renderer->addCommand(&_customCmd);
	rt->end();
	return Sprite::createWithTexture(rt->getSprite()->getTexture());
}
void DrawSprite::onDrawSprite03() {
	CCLOG("DrawSprite::onDrawSprite03");
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

Sprite* DrawSprite::createSprite04(cocos2d::Color4F bgColor, float textureWidth, float textureHeight) {
	texture = Sprite::create("Default.png")->getTexture();
	RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);
	rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	//CustomCommand _customCmd;
	_customCmd.init(rt->getGlobalZOrder());
	_customCmd.func = CC_CALLBACK_0(DrawSprite::onDrawSprite04, this);
	auto renderer = Director::getInstance()->getRenderer();
	renderer->addCommand(&_customCmd);
	rt->end();
	return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

void DrawSprite::onDrawSprite04() {
	CCLOG("DrawSprite::onDrawSprite04");
	kmGLPushMatrix();
	GL::bindTexture2D(texture->getName());
	texture->getGLProgram()->use();
	texture->getGLProgram()->setUniformsForBuiltins();
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, triangleStripPos);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, 0, textCoords);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, NUM_VERTEX);
	kmGLPopMatrix();
}