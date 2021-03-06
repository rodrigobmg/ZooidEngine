#ifndef __Z_GL_TEXTURE__
#define __Z_GL_TEXTURE__

#include "Renderer/IGPUTexture.h"

#include <GL/glew.h>

namespace ZE
{
	class GLTexture : public IGPUTexture
	{
	public:
		GLTexture() : m_textureBuffer(0) {}

		virtual void FromTexture(Texture* texture) override;
		virtual void release() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		GLuint m_textureBuffer;
	};
}
#endif
