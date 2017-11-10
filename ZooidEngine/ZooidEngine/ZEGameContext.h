#ifndef __ZE_GAME_CONTEXT__
#define __ZE_GAME_CONTEXT__

#include "ZEngine.h"

namespace ZE {
	class GameContext {
	public:
		GameContext() {}
		virtual ~GameContext() {}

		IRenderer* m_renderer;
		BufferManager* m_bufferManager;
		ShaderManager* m_shaderManager;
		DrawList* m_drawList;
		CameraManager* m_cameraManager;

		IRenderer* getRenderer() const { return m_renderer; }
		BufferManager* getBufferManager() const { return m_bufferManager; }
		ShaderManager* getShaderManager() const { return m_shaderManager; }
		DrawList* getDrawList() const { return m_drawList; }
		CameraManager* getCameraManager() const { return m_cameraManager; }
	};
}
#endif // __ZE_GAME_CONTEXT__