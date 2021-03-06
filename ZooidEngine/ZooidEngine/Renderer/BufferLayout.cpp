#include "BufferLayout.h"

#include <GL/glew.h>

namespace ZE {

	BufferLayoutManager* BufferLayoutManager::m_instance = nullptr;

	void BufferLayoutManager::Init()
	{
		m_instance = new BufferLayoutManager;
		m_instance->InitLayout();
	}

	ZE::BufferLayoutManager* BufferLayoutManager::getInstance()
	{
		return m_instance;
	}

	void BufferLayoutManager::Destroy()
	{
		m_instance->DestroyLayout();
		delete m_instance;
	}

	void BufferLayoutManager::InitLayout()
	{
		m_bufferLayout.reset(4);

		// Vertex : { Position, Color }
		BufferLayout* vertexColorLayout = new BufferLayout();
		vertexColorLayout->m_layouts.reset(2);
		vertexColorLayout->m_layouts.push_back({ 0, 3, DataType::FLOAT, 6 * sizeof(float), 0 });
		vertexColorLayout->m_layouts.push_back({ 1, 3, DataType::FLOAT, 6 * sizeof(float), 3 });
		
		m_bufferLayout.push_back(vertexColorLayout);

		// Vertex : { Postion, TexCoord }
		BufferLayout* vertexTexCoord = new BufferLayout();
		vertexTexCoord->m_layouts.reset(2);
		vertexTexCoord->m_layouts.push_back({ 0, 3, DataType::FLOAT, 5 * sizeof(float), 0 });
		vertexTexCoord->m_layouts.push_back({ 1, 3, DataType::FLOAT, 5 * sizeof(float), 3 });
		
		m_bufferLayout.push_back(vertexTexCoord);

		// Vertex : { Postion, Color, TexCoord }
		BufferLayout* texCoordLayout = new BufferLayout();
		texCoordLayout->m_layouts.reset(3);
		texCoordLayout->m_layouts.push_back({ 0, 3, DataType::FLOAT, 8 * sizeof(float), 0 });
		texCoordLayout->m_layouts.push_back({ 1, 3, DataType::FLOAT, 8 * sizeof(float), 3 });
		texCoordLayout->m_layouts.push_back({ 2, 2, DataType::FLOAT, 8 * sizeof(float), 6 });
		
		m_bufferLayout.push_back(texCoordLayout);

		// Vertex : { Postion, Normal, TexCoord }
		BufferLayout* normalTexCoordLayout = new BufferLayout();
		normalTexCoordLayout->m_layouts.reset(3);
		normalTexCoordLayout->m_layouts.push_back({ 0, 3, DataType::FLOAT, 8 * sizeof(float), 0 });
		normalTexCoordLayout->m_layouts.push_back({ 1, 3, DataType::FLOAT, 8 * sizeof(float), 3 });
		normalTexCoordLayout->m_layouts.push_back({ 2, 2, DataType::FLOAT, 8 * sizeof(float), 6 });

		m_bufferLayout.push_back(normalTexCoordLayout);
	}

	void BufferLayoutManager::DestroyLayout()
	{

		m_bufferLayout.clear();
	}

	ZE::BufferLayout* BufferLayoutManager::getBufferLayoutByFormat(int format)
	{
		return m_bufferLayout[format];
	}

}