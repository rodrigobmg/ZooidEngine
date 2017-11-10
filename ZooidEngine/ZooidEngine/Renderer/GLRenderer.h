#ifndef __ZE_GL_RENDERER__
#define __ZE_GL_RENDERER__

#include "IRenderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Math/Matrix4x4.h"

#define WIDTH 1280
#define HEIGHT 720

namespace ZE {
class GLRenderer : public IRenderer {
	
public:
	GLRenderer() {}
	virtual ~GLRenderer() {}

	virtual void Setup() override;
	virtual void BeginRender() override;
	virtual void EndRender() override;
	virtual void Clean() override;
	virtual void ClearScreen() override;
	virtual void ProcessShaderAction(ShaderAction* shaderAction) override;
	virtual void Draw(ShaderAction* shaderAction) override;
	virtual bool IsClose() override;

	virtual float GetHeight() const { return HEIGHT; }
	virtual float GetWidth() const { return WIDTH; }

	void SetShaderGlobal(ShaderAction* shaderAction);

	GLFWwindow* m_window;

	// #TODO Make shader for global instead saving the viewMatrix here
	Matrix4x4 m_viewMatrix;
	Matrix4x4 m_projMatrix;
};
}
#endif