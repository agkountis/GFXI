#ifndef BLADE_D3D11_IBO_H_
#define BLADE_D3D11_IBO_H_
#include "../IBO.h"
#include "../types.h"
#include <D3D/d3d11.h>

namespace Blade
{
	class D3D11IBO : public IBO
	{
	private:
		ComPtr<ID3D11Buffer> m_IndexBuffer;

	public:
		D3D11IBO() = default;

		bool Create(const std::vector<unsigned int>& indices) noexcept override;

		void Bind() const noexcept override;

		void Draw() const noexcept override;
	};
}

#endif //BLADE_D3D11_IBO_H_
