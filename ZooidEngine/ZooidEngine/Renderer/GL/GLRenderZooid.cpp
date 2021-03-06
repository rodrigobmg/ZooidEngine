#include "GLRenderZooid.h"

#include "GLRenderer.h"
#include "GLBufferData.h"
#include "GLBufferArray.h"
#include "GLTexture.h"
#include "GLShader.h"

#include "Memory/Handle.h"

namespace ZE
{

	Handle GLRenderZooid::CreateRenderBufferData()
	{
		Handle hRenderBufferData("Render Buffer Data", sizeof(GLBufferData));
		GLBufferData* pBufferData = new(hRenderBufferData) GLBufferData();
		return hRenderBufferData;
	}

	ZE::Handle GLRenderZooid::CreateRenderBufferArray()
	{
		Handle hRenderBufferArray("Render Buffer Array", sizeof(GLBufferArray));
		GLBufferArray* pBufferArray = new(hRenderBufferArray) GLBufferArray();
		return hRenderBufferArray;
	}

	ZE::Handle GLRenderZooid::CreateRenderTexture()
	{
		Handle hTexture("Render Texture", sizeof(GLTexture));
		GLTexture* pTexture = new(hTexture) GLTexture();
		return hTexture;
	}

	ZE::Handle GLRenderZooid::CreateShader()
	{
		Handle hShader("Render Shader", sizeof(GLShader));
		GLShader* pShader = new(hShader) GLShader();
		return hShader;
	}

	ZE::Handle GLRenderZooid::CreateShaderChain()
	{
		Handle hShaderChain("Render Shader Chain", sizeof(GLShaderChain));
		GLShaderChain* pShaderChain = new(hShaderChain) GLShaderChain();
		return hShaderChain;
	}

	void GLRenderZooid::Init()
	{
		Handle rendererHandle("GL Renderer", sizeof(GLRenderer));
		m_renderer = new(rendererHandle) GLRenderer();
		m_renderer->Setup();
	}
	
	void GLRenderZooid::Destroy()
	{
		// TODO Destroying GLRenderer
		m_renderer->Clean();
		m_renderer = nullptr;
	}

}
