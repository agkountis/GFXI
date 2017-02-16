#ifndef BLADE_D3D_RENDER_TARGET_H_
#define BLADE_D3D_RENDER_TARGET_H_
#include "../render_target.h"
#include "../types.h"
#include <D3D/d3d11.h>

namespace Blade
{
	class D3D11RenderTarget : public RenderTarget
	{
	private:
		ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		ComPtr<ID3D11DepthStencilView> m_DepthStencilView;

		ComPtr<ID3D11Texture2D> m_ColorAttachment;
		ComPtr<ID3D11Texture2D> m_DepthAttachment;

		ComPtr<ID3D11ShaderResourceView> m_ColorAttachmentSrv;
		ComPtr<ID3D11ShaderResourceView> m_DepthAttachmentSrv;

		bool m_MSAA{ false };
		int m_SampleCount{ 1 };

	public:
		D3D11RenderTarget() = default;

		D3D11RenderTarget(const Vec2i& size,
		                  bool MSAA,
		                  int sampleCount) : RenderTarget(size),
		                                      m_MSAA(MSAA),
		                                      m_SampleCount(sampleCount)
		{
		}

		bool Create(const Vec2i& size) override;

		bool Bind(RenderTargetBindType bindType) const override;

		bool Unbind() const override;

		void Clear(float* color) const noexcept;

		ID3D11ShaderResourceView* GetColorAttachment() const noexcept
		{
			return m_ColorAttachmentSrv.Get();
		}

		ID3D11ShaderResourceView* GetDepthAttachment() const noexcept
		{
			return m_DepthAttachmentSrv.Get();
		}
	};
}

#endif //BLADE_D3D_RENDER_TARGET_H_
