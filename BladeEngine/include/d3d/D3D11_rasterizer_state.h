#ifndef BLADE_D3D11_RASTERIZER_STATE_H_
#define BLADE_D3D11_RASTERIZER_STATE_H_
#include "../render_state.h"
#include "../types.h"
#include "D3D11_IBO.h"

namespace Blade
{
	class D3D11RasterizerState : public RenderState
	{
	private:
		ComPtr<ID3D11RasterizerState> m_RasterizerState;

	public:
		explicit D3D11RasterizerState(RenderStateType renderStateType);

		void Set() const noexcept override;
	};
}

#endif //BLADE_D3D11_RASTERIZER_STATE_H_
