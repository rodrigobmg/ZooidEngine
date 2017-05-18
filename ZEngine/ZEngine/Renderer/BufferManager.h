#ifndef __ZE_BUFFER_MANAGER__
#define __ZE_BUFFER_MANAGER__

#include "BufferData.h"
#include "GPUBufferData.h"
#include "GPUBufferArray.h"
#include "BufferLayout.h"
#include "../GameObjectModel/Component.h"

#include <vector>

namespace ZE {
class BufferManager : public Component {
	
	DEFINE_CLASS(BufferManager)

	static BufferManager* m_instance;

	BufferManager();

public:
	
	static BufferManager* getInstance();

	static void Init();
	static void Destroy();

	GPUBufferData* createGPUBufferFromBuffer(BufferData* _bufferData);
	GPUBufferArray* createBufferArray(BufferData* _vertexBuffer, BufferData* _indexBuffer, BufferData* _gpuBuffer);

	std::vector<BufferData*> m_buffers;
	std::vector<GPUBufferData*> m_GPUBuffers;
	std::vector<GPUBufferArray*> m_GPUBufferArrays;

	BufferLayoutManager* m_bufferLayoutManager;
};
}
#endif
