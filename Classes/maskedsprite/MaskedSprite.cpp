#include "maskedsprite\MaskedSprite.h"

using namespace maskedsprite;

Sprite * maskedsprite::MaskedSprite::initWithSprite(Sprite * sprite, Sprite * maskSprite)
{
	self = [(HJMaskedSprite *)sprite retain];
	if (self) {
		const GLchar * fragmentSource = (GLchar*)[[NSString stringWithContentsOfFile : [CCFileUtils fullPathFromRelativePath : @"Mask.fsh"]
			encoding:NSUTF8StringEncoding error : nil] UTF8String];

		self.shaderProgram = [[CCGLProgram alloc] initWithVertexShaderByteArray:ccPositionTextureA8Color_vert
			fragmentShaderByteArray : fragmentSource];
		[self.shaderProgram addAttribute : kCCAttributeNamePosition index : kCCVertexAttrib_Position];
		[self.shaderProgram addAttribute : kCCAttributeNameTexCoord index : kCCVertexAttrib_TexCoords];
		[self.shaderProgram addAttribute : kCCAttributeNameColor index : kCCVertexAttrib_Color];
		[self.shaderProgram link];
		[self.shaderProgram updateUniforms];

		_maskLocation = glGetUniformLocation(self.shaderProgram->program_, "u_overlayTexture");
		glUniform1i(_maskLocation, 1);
		_maskTexture = [[CCTextureCache sharedTextureCache] addImage:maskFile];
		[_maskTexture setAliasTexParameters];

		[self.shaderProgram use];
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, [_maskTexture name]);
		glActiveTexture(GL_TEXTURE0);

	}
	return self;
}

Sprite * maskedsprite::MaskedSprite::initWithSprite(Sprite * sprite, const char * maskFile)
{
	self = [(HJMaskedSprite *)sprite retain];
	if (self) {
		const GLchar * fragmentSource = (GLchar*)[[NSString stringWithContentsOfFile : [CCFileUtils fullPathFromRelativePath : @"Mask.fsh"]
			encoding:NSUTF8StringEncoding error : nil] UTF8String];

		self.shaderProgram = [[CCGLProgram alloc] initWithVertexShaderByteArray:ccPositionTextureA8Color_vert
			fragmentShaderByteArray : fragmentSource];
		[self.shaderProgram addAttribute : kCCAttributeNamePosition index : kCCVertexAttrib_Position];
		[self.shaderProgram addAttribute : kCCAttributeNameTexCoord index : kCCVertexAttrib_TexCoords];
		[self.shaderProgram addAttribute : kCCAttributeNameColor index : kCCVertexAttrib_Color];
		[self.shaderProgram link];
		[self.shaderProgram updateUniforms];

		_maskLocation = glGetUniformLocation(self.shaderProgram->program_, "u_overlayTexture");
		glUniform1i(_maskLocation, 1);
		_maskTexture = [[CCTextureCache sharedTextureCache] addImage:maskFile];
		[_maskTexture setAliasTexParameters];

		[self.shaderProgram use];
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, [_maskTexture name]);
		glActiveTexture(GL_TEXTURE0);

	}
	return self;
}

Sprite * maskedsprite::MaskedSprite::initWithSpriteFrame(SpriteFrame * spriteFrame, const char * maskFile)
{
	self = [(HJMaskedSprite *)sprite retain];
	if (self) {
		const GLchar * fragmentSource = (GLchar*)[[NSString stringWithContentsOfFile : [CCFileUtils fullPathFromRelativePath : @"Mask.fsh"]
			encoding:NSUTF8StringEncoding error : nil] UTF8String];

		self.shaderProgram = [[CCGLProgram alloc] initWithVertexShaderByteArray:ccPositionTextureA8Color_vert
			fragmentShaderByteArray : fragmentSource];
		[self.shaderProgram addAttribute : kCCAttributeNamePosition index : kCCVertexAttrib_Position];
		[self.shaderProgram addAttribute : kCCAttributeNameTexCoord index : kCCVertexAttrib_TexCoords];
		[self.shaderProgram addAttribute : kCCAttributeNameColor index : kCCVertexAttrib_Color];
		[self.shaderProgram link];
		[self.shaderProgram updateUniforms];

		_maskLocation = glGetUniformLocation(self.shaderProgram->program_, "u_overlayTexture");
		glUniform1i(_maskLocation, 1);
		_maskTexture = [[CCTextureCache sharedTextureCache] addImage:maskFile];
		[_maskTexture setAliasTexParameters];

		[self.shaderProgram use];
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, [_maskTexture name]);
		glActiveTexture(GL_TEXTURE0);

	}
	return self;
}

Sprite * maskedsprite::MaskedSprite::initWithFile(const char * file, const char * maskFile)
{
	self = [super initWithFile : file];
	if (self) {
		const GLchar * fragmentSource = (GLchar*)[[NSString stringWithContentsOfFile : [CCFileUtils fullPathFromRelativePath : @"Mask.fsh"]
			encoding:NSUTF8StringEncoding error : nil] UTF8String];

		self.shaderProgram = [[CCGLProgram alloc] initWithVertexShaderByteArray:ccPositionTextureA8Color_vert
			fragmentShaderByteArray : fragmentSource];
		[self.shaderProgram addAttribute : kCCAttributeNamePosition index : kCCVertexAttrib_Position];
		[self.shaderProgram addAttribute : kCCAttributeNameTexCoord index : kCCVertexAttrib_TexCoords];
		[self.shaderProgram addAttribute : kCCAttributeNameColor index : kCCVertexAttrib_Color];
		[self.shaderProgram link];
		[self.shaderProgram updateUniforms];

		_maskLocation = glGetUniformLocation(self.shaderProgram->program_, "u_overlayTexture");
		glUniform1i(_maskLocation, 1);
		_maskTexture = [[CCTextureCache sharedTextureCache] addImage:maskFile];
		[_maskTexture setAliasTexParameters];

		[self.shaderProgram use];
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, [_maskTexture name]);
		glActiveTexture(GL_TEXTURE0);


	}

	return self;
}

Sprite * maskedsprite::MaskedSprite::initWithFile(const char * file, SpriteFrame * mask)
{
	self = [super initWithFile : file];
	if (self) {
		const GLchar * fragmentSource = (GLchar*)[[NSString stringWithContentsOfFile : [CCFileUtils fullPathFromRelativePath : @"Mask.fsh"]
			encoding:NSUTF8StringEncoding error : nil] UTF8String];

		self.shaderProgram = [[CCGLProgram alloc] initWithVertexShaderByteArray:ccPositionTextureA8Color_vert
			fragmentShaderByteArray : fragmentSource];
		[self.shaderProgram addAttribute : kCCAttributeNamePosition index : kCCVertexAttrib_Position];
		[self.shaderProgram addAttribute : kCCAttributeNameTexCoord index : kCCVertexAttrib_TexCoords];
		[self.shaderProgram addAttribute : kCCAttributeNameColor index : kCCVertexAttrib_Color];
		[self.shaderProgram link];
		[self.shaderProgram updateUniforms];

		_maskLocation = glGetUniformLocation(self.shaderProgram->program_, "u_overlayTexture");
		glUniform1i(_maskLocation, 1);
		_maskTexture = [[maskSprite texture] retain];
		[_maskTexture setAliasTexParameters];

		[self.shaderProgram use];
		ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, [_maskTexture name]);
		glActiveTexture(GL_TEXTURE0);

	}

	return self;
}
