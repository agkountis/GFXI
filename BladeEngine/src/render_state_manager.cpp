#include "render_state_manager.h"
#include "d3d/D3D11_blend_state.h"
#include "d3d/D3D11_rasterizer_state.h"
#include "d3d/D3D11_depth_stencil_state.h"

namespace Blade
{
	std::map<RenderStateType, RenderState*> RenderStateManager::m_RenderStates;

	RenderStateManager::~RenderStateManager()
	{
		for (auto render_state : m_RenderStates)
		{
			delete render_state.second;
		}

		m_RenderStates.clear();
	}


	RenderStateManager::RenderStateManager()
	{
	}

	void RenderStateManager::Initialize() noexcept
	{
#if defined(BLADE_BUILD_D3D)
		m_RenderStates[RenderStateType::BS_BLEND_DISSABLED] = new D3D11BlendState{ RenderStateType::BS_BLEND_DISSABLED };
		m_RenderStates[RenderStateType::BS_BLEND_ADDITIVE] = new D3D11BlendState{ RenderStateType::BS_BLEND_ADDITIVE };
		m_RenderStates[RenderStateType::BS_BLEND_ALPHA] = new D3D11BlendState{ RenderStateType::BS_BLEND_ALPHA };
		m_RenderStates[RenderStateType::RS_CULL_FRONT] = new D3D11RasterizerState{ RenderStateType::RS_CULL_FRONT };
		m_RenderStates[RenderStateType::RS_CULL_BACK] = new D3D11RasterizerState{ RenderStateType::RS_CULL_BACK };
		m_RenderStates[RenderStateType::RS_DRAW_SOLID] = new D3D11RasterizerState{ RenderStateType::RS_DRAW_SOLID };
		m_RenderStates[RenderStateType::RS_DRAW_WIRE] = new D3D11RasterizerState{ RenderStateType::RS_DRAW_WIRE };
		m_RenderStates[RenderStateType::DSS_DEPTH_TEST_ENABLE] = new D3D11DepthStencilState{ RenderStateType::DSS_DEPTH_TEST_ENABLE };
		m_RenderStates[RenderStateType::DSS_DEPTH_TEST_DISABLE] = new D3D11DepthStencilState{ RenderStateType::DSS_DEPTH_TEST_DISABLE };
		m_RenderStates[RenderStateType::DSS_DEPTH_MASK_0] = new D3D11DepthStencilState{ RenderStateType::DSS_DEPTH_MASK_0 };
		m_RenderStates[RenderStateType::DSS_DEPTH_MASK_1] = new D3D11DepthStencilState{ RenderStateType::DSS_DEPTH_MASK_1 };
#else
#endif
	}

	void RenderStateManager::Set(RenderStateType render_state) noexcept
	{
		m_RenderStates[render_state]->Set();
	}
}
