#include "render_state_manager.h"
#include "d3d/D3D11_blend_state.h"
#include "d3d/D3D11_rasterizer_state.h"
#include "d3d/D3D11_depth_stencil_state.h"

namespace Blade
{
	void RenderStateManager::Initialize() noexcept
	{
#ifdef BLADE_BUILD_D3D
		m_RenderStates[RenderStateType::BS_BLEND_DISSABLED] = std::make_unique<D3D11BlendState>(RenderStateType::BS_BLEND_DISSABLED);
		m_RenderStates[RenderStateType::BS_BLEND_ADDITIVE] = std::make_unique<D3D11BlendState>(RenderStateType::BS_BLEND_ADDITIVE);
		m_RenderStates[RenderStateType::BS_BLEND_ALPHA] = std::make_unique<D3D11BlendState>(RenderStateType::BS_BLEND_ALPHA);
		m_RenderStates[RenderStateType::RS_CULL_FRONT] = std::make_unique<D3D11RasterizerState>(RenderStateType::RS_CULL_FRONT);
		m_RenderStates[RenderStateType::RS_CULL_BACK] = std::make_unique<D3D11RasterizerState>(RenderStateType::RS_CULL_BACK);
		m_RenderStates[RenderStateType::RS_DRAW_SOLID] = std::make_unique<D3D11RasterizerState>(RenderStateType::RS_DRAW_SOLID);
		m_RenderStates[RenderStateType::RS_DRAW_WIRE] = std::make_unique<D3D11RasterizerState>(RenderStateType::RS_DRAW_WIRE);
		m_RenderStates[RenderStateType::DSS_DEPTH_TEST_ENABLE] = std::make_unique<D3D11DepthStencilState>(RenderStateType::DSS_DEPTH_TEST_ENABLE);
		m_RenderStates[RenderStateType::DSS_DEPTH_TEST_DISABLE] = std::make_unique<D3D11DepthStencilState>(RenderStateType::DSS_DEPTH_TEST_DISABLE);
		m_RenderStates[RenderStateType::DSS_DEPTH_MASK_0] = std::make_unique<D3D11DepthStencilState>(RenderStateType::DSS_DEPTH_MASK_0);
		m_RenderStates[RenderStateType::DSS_DEPTH_MASK_1] = std::make_unique<D3D11DepthStencilState>(RenderStateType::DSS_DEPTH_MASK_1);
#else
#endif
	}

	void RenderStateManager::Set(RenderStateType render_state) noexcept
	{
		m_RenderStates[render_state]->Set();
	}
}
