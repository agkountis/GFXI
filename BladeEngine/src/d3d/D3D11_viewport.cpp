#include "d3d/D3D11_viewport.h"
#include "engine_context.h"

namespace Blade
{
	void D3D11Viewport::Set() const noexcept
	{
		D3D11_VIEWPORT viewport;
		viewport.TopLeftX = GetRect().x;
		viewport.TopLeftY = GetRect().y;
		viewport.Width = static_cast<float>(GetRect().z);
		viewport.Height = static_cast<float>(GetRect().w);
		viewport.MinDepth = m_MinDepth;
		viewport.MaxDepth = m_MaxDepth;

		D3D11Context* ctx{ EngineContext::GetGAPIContext() };

		ID3D11DeviceContext* context{ ctx->GetDeviceContext() };
		
		context->RSSetViewports(1, &viewport);
	}
}
