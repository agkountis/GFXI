#ifndef BLADE_D3D11_VBO_H_
#define BLADE_D3D11_VBO_H_
#include "../VBO.h"
#include <D3D/d3d11.h>
#include "../types.h"

namespace Blade
{
	class D3D11VBO : public VBO
	{
	private:
		ComPtr<ID3D11Buffer> m_VertexBuffer;

	public:
		D3D11VBO() = default;

		bool Create(const std::vector<Vertex>& vertices, PrimitiveTopology primitiveTopology) noexcept override;

		void Bind() const noexcept override;

		void Draw() const noexcept override;
	};
}

#endif //BLADE_D3D11_VBO_H_
