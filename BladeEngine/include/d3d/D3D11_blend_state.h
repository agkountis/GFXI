#ifndef BLADE_D3D11_BLEND_STATE_H_
#define BLADE_D3D11_BLEND_STATE_H_
#include "render_state.h"
#include "types.h"
#include "D3D/d3d11.h"

namespace Blade
{
	class D3D11BlendState : public RenderState
	{
	private:
		ComPtr<ID3D11BlendState> m_BlendState;

	public:
		explicit D3D11BlendState(RenderStateType render_state_type);

		void Set() const noexcept override;
	};
}

#endif //BLADE_D3D11_BLEND_STATE_H_
