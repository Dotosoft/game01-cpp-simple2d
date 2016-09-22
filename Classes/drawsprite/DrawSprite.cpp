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

Sprite* DrawSprite::createSprite05(float textureWidth, float textureHeight) {
	
	// select between a type of stripe
	EStripeType stripe_type = (EStripeType)((int)(CCRANDOM_0_1() * (E_STRIPE_SLOPE_DOWN + 1)));

	RenderTexture *rt = RenderTexture::create(textureWidth, textureHeight);
	rt->beginWithClear(0, 0, 0, 0);
	//CustomCommand _customCmd;
	_customCmd.init(rt->getGlobalZOrder());
	_customCmd.func = CC_CALLBACK_0(DrawSprite::onDrawSprite05, this, stripe_type, 8);
	auto renderer = Director::getInstance()->getRenderer();
	renderer->addCommand(&_customCmd);

	RenderNoise();

	rt->end();
	return Sprite::createWithTexture(rt->getSprite()->getTexture());
}

void DrawSprite::onDrawSprite05(EStripeType stripe_type, int num_stripes) {
	this->RenderStripes(stripe_type, num_stripes);
	this->RenderGradient();
	this->RenderHighlight();
	this->RenderTopBorder();
	// this->RenderNoise();
}

void DrawSprite::RenderStripes(EStripeType stripe_type, int num_stripes)
{
	// allocate memory for the position & colour arrays
	ccVertex2F* vertices = (ccVertex2F*)malloc(sizeof(ccVertex2F) * num_stripes * 6);
	ccColor4F* colors = (ccColor4F*)malloc(sizeof(ccColor4F) * num_stripes * 6);

	// initialise variables
	int num_vertices = 0;
	float x1 = 0.0f, x2 = 0.0f, y1 = 0.0f, y2 = 0.0f, dx = 0.0f, dy = 0.0f;

	// select between two colours or many colours
	bool two_colors = (CCRANDOM_MINUS1_1() > 0);
	ccColor4F color1 = GameGlobals::GetRandomColor();
	ccColor4F color2 = GameGlobals::GetRandomColor();
	ccColor4F c;

	if (stripe_type == E_STRIPE_HORIZONTAL)
	{
		// initialise variables for the horizontal stripe
		dx = 0;
		dy = (float)STRIPE_TEXTURE_SIZE / (float)num_stripes;

		x1 = 0;
		y1 = 0;

		x2 = STRIPE_TEXTURE_SIZE;
		y2 = 0;

		// generate position & colour for each vertex of the stripe
		for (int i = 0; i < num_stripes; ++i)
		{
			c = two_colors ? (i % 2 ? color1 : color2) : GameGlobals::GetRandomColor();

			colors[num_vertices] = c;
			vertices[num_vertices++] = vertex2(x1, y1);
			colors[num_vertices] = c;
			vertices[num_vertices++] = vertex2(x2, y2);
			colors[num_vertices] = c;
			vertices[num_vertices++] = vertex2(x1, y1 + dy);
			colors[num_vertices] = c;
			vertices[num_vertices++] = vertices[num_vertices - 2];
			colors[num_vertices] = c;
			vertices[num_vertices++] = vertices[num_vertices - 2];
			colors[num_vertices] = c;
			vertices[num_vertices++] = vertex2(x2, y2 + dy);

			y1 += dy;
			y2 += dy;
		}
	}
	else
	{
		// initialise variables based on type of stripe
		dx = (float)STRIPE_TEXTURE_SIZE * 2 / (float)num_stripes;
		dy = 0;

		x1 = -STRIPE_TEXTURE_SIZE;
		y1 = (stripe_type == E_STRIPE_SLOPE_DOWN) ? 0 : STRIPE_TEXTURE_SIZE;

		x2 = 0;
		y2 = (stripe_type == E_STRIPE_SLOPE_DOWN) ? STRIPE_TEXTURE_SIZE : 0;

		// generate position & colours for two stripes at a time
		for (int i = 0; i < num_stripes / 2; ++i)
		{
			c = two_colors ? (i % 2 ? color1 : color2) : GameGlobals::GetRandomColor();

			for (int j = 0; j < 2; ++j)
			{
				colors[num_vertices] = c;
				vertices[num_vertices++] = vertex2(x1 + j * STRIPE_TEXTURE_SIZE, y1);
				colors[num_vertices] = c;
				vertices[num_vertices++] = vertex2(x1 + j * STRIPE_TEXTURE_SIZE + dx, y1);
				colors[num_vertices] = c;
				vertices[num_vertices++] = vertex2(x2 + j * STRIPE_TEXTURE_SIZE, y2);
				colors[num_vertices] = c;
				vertices[num_vertices++] = vertices[num_vertices - 2];
				colors[num_vertices] = c;
				vertices[num_vertices++] = vertices[num_vertices - 2];
				colors[num_vertices] = c;
				vertices[num_vertices++] = vertex2(x2 + j * STRIPE_TEXTURE_SIZE + dx, y2);
			}

			x1 += dx;
			x2 += dx;
		}
	}

	// we're dealing with position & colour data here
	// setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(GLProgram::SHADER_NAME_POSITION_COLOR));
	CC_NODE_DRAW_SETUP();

	// enable position & colour attributes
	GL::enableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
	// pass position & colour data
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
	// set the blend function
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	// draw it...GL_TRIANGLES style!
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)num_vertices);

	// free what we allocated on top
	free(vertices);
	free(colors);
}

void DrawSprite::RenderGradient()
{
	// declare arrays for position & colour data
	ccVertex2F vertices[4];
	ccColor4F colors[4];

	// gradient will be light on top & dark at the bottom
	vertices[0] = vertex2(0, 0);
	vertices[1] = vertex2(STRIPE_TEXTURE_SIZE, 0);
	vertices[2] = vertex2(0, STRIPE_TEXTURE_SIZE);
	vertices[3] = vertex2(STRIPE_TEXTURE_SIZE, STRIPE_TEXTURE_SIZE);
	colors[0] = ccc4f(0.0f, 0.0f, 0.0f, 0.0f);
	colors[1] = ccc4f(0.0f, 0.0f, 0.0f, 0.0f);
	colors[2] = ccc4f(0.0f, 0.0f, 0.0f, 0.75f);
	colors[3] = ccc4f(0.0f, 0.0f, 0.0f, 0.75f);

	// we're dealing with position & colour data here
	// setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(GLProgram::SHADER_NAME_POSITION_COLOR));
	CC_NODE_DRAW_SETUP();

	// enable position & colour attributes
	GL::enableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
	// pass position & colour data
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
	// draw it...GL_TRIANGLE_STRIP style!
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void DrawSprite::RenderHighlight()
{
	// declare arrays for position & colour data
	ccVertex2F vertices[4];
	ccColor4F colors[4];

	// highlight will be yellowish on top & nothing at the bottom
	vertices[0] = vertex2(0, 0);
	vertices[1] = vertex2(STRIPE_TEXTURE_SIZE, 0);
	vertices[2] = vertex2(0, STRIPE_TEXTURE_SIZE / 3);
	vertices[3] = vertex2(STRIPE_TEXTURE_SIZE, STRIPE_TEXTURE_SIZE / 3);
	colors[0] = ccc4f(1.0f, 1.0f, 0.5f, 0.4f);
	colors[1] = ccc4f(1.0f, 1.0f, 0.5f, 0.4f);
	colors[2] = ccc4f(1.0f, 1.0f, 0.5f, 0.0f);
	colors[3] = ccc4f(1.0f, 1.0f, 0.5f, 0.0f);

	// we're dealing with position & colour data here
	// setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(GLProgram::SHADER_NAME_POSITION_COLOR));
	CC_NODE_DRAW_SETUP();

	// enable position & colour attributes
	GL::enableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
	// pass position & colour data
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
	// set the blend function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// draw it...GL_TRIANGLE_STRIP style!
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void DrawSprite::RenderTopBorder()
{
	// declare arrays for position & colour data
	ccVertex2F vertices[4];
	ccColor4F colors[4];

	// semi-transparent grey border to indicate the surface of the hill
	vertices[0] = vertex2(0, 0);
	vertices[1] = vertex2(STRIPE_TEXTURE_SIZE, 0);
	vertices[2] = vertex2(0, 3);
	vertices[3] = vertex2(STRIPE_TEXTURE_SIZE, 3);
	colors[0] = ccc4f(0.3255f, 0.3255f, 0.3255f, 0.75f);
	colors[1] = ccc4f(0.3255f, 0.3255f, 0.3255f, 0.75f);
	colors[2] = ccc4f(0.3255f, 0.3255f, 0.3255f, 0.75f);
	colors[3] = ccc4f(0.3255f, 0.3255f, 0.3255f, 0.75f);

	// we're dealing with position & colour data here
	// setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(GLProgram::SHADER_NAME_POSITION_COLOR));
	CC_NODE_DRAW_SETUP();

	// enable position & colour attributes
	GL::enableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
	// pass position & colour data
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
	// set the blend function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// draw it...GL_TRIANGLE_STRIP style!
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void DrawSprite::RenderNoise()
{
	// create a sprite with readymade noise
	CCSprite* noise = CCSprite::create("noise1.png");
	// set the proper blend function
	ccBlendFunc blend_func;
	blend_func.src = GL_DST_COLOR;
	blend_func.dst = GL_ZERO;
	noise->setBlendFunc(blend_func);
	// position the sprite at the centre of the texture
	noise->setPosition(Vec2(STRIPE_TEXTURE_SIZE / 2, STRIPE_TEXTURE_SIZE / 2));
	// call visit to render the sprite...twice gives added contrast
	noise->visit();
	noise->visit();
}