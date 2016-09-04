#include "maskedsprite\MaskedSprite.h"

using namespace maskedsprite;

MaskedSprite * MaskedSprite::createWithSprite(Sprite* sprite, std::string andImageOverlay)
{
	auto self = new MaskedSprite();
	//////////////////////////////
	// 1. super init first
	if (!self->init())
	{
		return nullptr;
	}

	GLchar * fragmentSource = (GLchar*)String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("maskedsprite/Mask.fsh").c_str())->getCString();
	sprite->getGLProgram()->initWithByteArrays(ccPositionTextureA8Color_vert, fragmentSource);
	// self->getShaderProgram()->initWithByteArrays(ccPositionTextureColor_noMVP_vert, fragmentSource);

	self->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	self->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	self->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	self->getGLProgram()->link();
	self->getGLProgram()->updateUniforms();

	self->setMaskLocation(glGetUniformLocation(self->getGLProgram()->getProgram(), "u_overlayTexture"));
	glUniform1i(self->getMaskLocation(), 1);
	self->setMaskTexture(TextureCache::getInstance()->addImage(andImageOverlay));
	self->getMaskTexture()->setAliasTexParameters();

	self->getGLProgram()->use();
	ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, self->getMaskTexture()->getName());
	glActiveTexture(GL_TEXTURE0);

	return self;
}

MaskedSprite * MaskedSprite::createWithSprite(Sprite* sprite, Sprite* andMaskSprite)
{
	auto self = new MaskedSprite();
	//////////////////////////////
	// 1. super init first
	if (!self->init())
	{
		return nullptr;
	}

	GLchar * fragmentSource = (GLchar*)String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("maskedsprite/Mask.fsh").c_str())->getCString();
	self->getShaderProgram()->initWithByteArrays(ccPositionTextureA8Color_vert, fragmentSource);

	self->getShaderProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	self->getShaderProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	self->getShaderProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	self->getShaderProgram()->link();
	self->getShaderProgram()->updateUniforms();

	self->setMaskLocation(glGetUniformLocation(self->getShaderProgram()->getProgram(), "u_overlayTexture"));
	glUniform1i(self->getMaskLocation(), 1);
	self->setMaskTexture(andMaskSprite->getTexture());
	self->getMaskTexture()->setAliasTexParameters();

	self->getShaderProgram()->use();
	ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, self->getMaskTexture()->getName());
	glActiveTexture(GL_TEXTURE0);

	return self;
}

MaskedSprite * MaskedSprite::createWithFile(std::string file, Sprite* andMaskSprite)
{
	auto self = new MaskedSprite();
	//////////////////////////////
	// 1. super init first
	if (!self->initWithFile(file))
	{
		return nullptr;
	}

	GLchar * fragmentSource = (GLchar*)String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("maskedsprite/Mask.fsh").c_str())->getCString();
	self->getShaderProgram()->initWithByteArrays(ccPositionTextureA8Color_vert, fragmentSource);

	self->getShaderProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	self->getShaderProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	self->getShaderProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	self->getShaderProgram()->link();
	self->getShaderProgram()->updateUniforms();

	self->setMaskLocation(glGetUniformLocation(self->getShaderProgram()->getProgram(), "u_overlayTexture"));
	glUniform1i(self->getMaskLocation(), 1);
	self->setMaskTexture(andMaskSprite->getTexture());
	self->getMaskTexture()->setAliasTexParameters();

	self->getShaderProgram()->use();
	ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, self->getMaskTexture()->getName());
	glActiveTexture(GL_TEXTURE0);

	return self;
}

MaskedSprite * MaskedSprite::createWithFile(std::string file, std::string maskFile)
{
	auto self = new MaskedSprite();
	//////////////////////////////
	// 1. super init first
	if (!self->initWithFile(file))
	{
		return nullptr;
	}

	GLchar * fragmentSource = (GLchar*)String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("maskedsprite/Mask.fsh").c_str())->getCString();
	self->getGLProgram()->initWithByteArrays(ccPositionTextureA8Color_vert, fragmentSource);

	self->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	self->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	self->getGLProgram()->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	self->getGLProgram()->link();
	self->getGLProgram()->updateUniforms();

	self->setMaskLocation(glGetUniformLocation(self->getGLProgram()->getProgram(), "u_overlayTexture"));
	glUniform1i(self->getMaskLocation(), 1);
	self->setMaskTexture(TextureCache::getInstance()->addImage(maskFile));
	self->getMaskTexture()->setAliasTexParameters();

	self->getGLProgram()->use();
	ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, self->getMaskTexture()->getName());
	glActiveTexture(GL_TEXTURE0);

	return self;
}

/*
void MaskedSprite::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) {

	CC_NODE_DRAW_SETUP();

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
	ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// [shaderProgram_ setUniformForModelViewProjectionMatrix];
	this->getShaderProgram()->setUniformsForBuiltins();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, getTexture()->getName());
	glUniform1i(this->getTextureLocation(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, getMaskTexture()->getName());
	glUniform1i(this->getMaskLocation(), 1);

	this->getQuad();

	#define kQuadSize sizeof(getQuad().bl)
	long offset = (long) &getQuad();

	// vertex
	auto diff = offsetof(ccV3F_C4B_T2F, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// texCoods
	diff = offsetof(ccV3F_C4B_T2F, texCoords);
	glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));

	// color
	diff = offsetof(ccV3F_C4B_T2F, colors);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glActiveTexture(GL_TEXTURE0);
}
*/