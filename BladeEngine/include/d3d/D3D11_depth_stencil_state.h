#ifndef BLADE_D3D11_DEPTH_STENCIL_STATE_H_
#define BLADE_D3D11_DEPTH_STENCIL_STATE_H_
#include "render_state.h"
#include "../types.h"
#include "D3D/D3D11.h"

namespace Blade
{
	class D3D11DepthStencilState : public RenderState
	{
	private:
		ComPtr<ID3D11DepthStencilState> m_DepthStencilState;

	public:
		explicit D3D11DepthStencilState(RenderStateType renderStateType);

		void Set() const noexcept override;
	};
}

#endif //BLADE_D3D11_DEPTH_STENCIL_STATE_H_
