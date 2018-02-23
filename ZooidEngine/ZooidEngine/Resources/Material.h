#ifndef __ZE_MATERIAL_H__
#define __ZE_MATERIAL_H__

#include "ZEngineIncl.h"

#include "Utils/Array.h"
#include "Utils/PrimitiveTypes.h"
#include "Renderer/ShaderAction.h"
#include "Math/Vector3.h"

namespace ZE
{
	class IGPUTexture;
	class GameContext;

	enum class TextureType : UInt8
	{
		DIFFUSE = 1,
		SPECULAR = 2
	};

	struct MaterialTexture
	{
		IGPUTexture* texture;
		TextureType type;
	};

	class Material : public Object
	{
		DEFINE_CLASS(Material)

	public:

		Material() 
			: m_Ka(0.0f, 0.0f, 0.0f),
			m_Kd(1.0f, 1.0f, 1.0f),
			m_Ks(1.0f, 1.0f, 1.0f)
		{
		}

		Array<MaterialTexture, true> m_textures;
		Float32 m_shininess;
		Vector3 m_Ka;
		Vector3 m_Kd;
		Vector3 m_Ks;

		void Bind(ShaderAction& shaderAction);
	};
}
#endif
