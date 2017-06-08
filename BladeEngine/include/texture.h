#ifndef BLADE_TEXTURE_H_
#define BLADE_TEXTURE_H_
#include "resource.h"

namespace Blade
{
	/*
	\brief Specified the type of a texture.
	*/
	enum TextureType
	{
		TEX_DIFFUSE,
		TEX_SPECULAR,
		TEX_NORMAL,
		TEX_EMISSION,
		TEX_AMBIENT_OCCLUSION,
		SUPPORTED_TEX_COUNT
	};

	/*
	\brief Texture class of the engine
	*/
	class Texture : public Resource
	{
	private:
		/*
		\brief Texture type of the engine.
		*/
		TextureType m_TextureType;

	public:
		Texture() = default;

		explicit Texture(TextureType textureType) : m_TextureType{ textureType }
		{
		}

		virtual void Bind() const noexcept = 0;

		void SetTextureType(TextureType texture_type) noexcept
		{
			m_TextureType = texture_type;
		}

		TextureType GetTextureType() const noexcept
		{
			return m_TextureType;
		}
	};
}

#endif //BLADE_TEXTURE_H_
