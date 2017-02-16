#ifndef GLACIER_D3D11_TEXTURE_H_
#define GLACIER_D3D11_TEXTURE_H_
#include "texture.h"
#include "types.h"
#include "D3D/D3D11.h"

namespace Blade
{
	class D3D11_texture : public Texture
	{
	private:
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;

	public:
		D3D11_texture() = default;

		explicit D3D11_texture(TextureType textureType) : Texture{ textureType }
		{
		}

		bool Load(const std::wstring& fileName) noexcept override;

		void Bind() const noexcept override;
	};
}

#endif
