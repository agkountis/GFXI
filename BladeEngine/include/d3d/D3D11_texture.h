#ifndef BLADE_D3D11_TEXTURE_H_
#define BLADE_D3D11_TEXTURE_H_
#include "texture.h"
#include "types.h"
#include "D3D/D3D11.h"

namespace Blade
{
	class D3D11Texture : public Texture
	{
	private:
		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;

	public:
		D3D11Texture() = default;

		explicit D3D11Texture(TextureType textureType) : Texture{ textureType }
		{
		}

		bool Load(const std::wstring& fileName) noexcept override;

		void Bind() const noexcept override;
	};
}

#endif //BLADE_D3D11_TEXTURE_H_
