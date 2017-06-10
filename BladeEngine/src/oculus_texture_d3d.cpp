#ifdef BLADE_BUILD_OVR

#include "oculus_texture_d3d.h"
#include "engine_context.h"
#include <OVR/OVR_CAPI_D3D.h>

namespace Blade
{
	OculusTextureD3D::OculusTextureD3D() :
		m_Session{ nullptr },
		m_TextureChain{ nullptr }
	{
	}

	bool OculusTextureD3D::Initialize(ovrSession session, int sizeW, int sizeH)
	{
		m_Session = session;

		ovrTextureSwapChainDesc desc = {};
		desc.Type = ovrTexture_2D;
		desc.ArraySize = 1;
		desc.Format = OVR_FORMAT_R8G8B8A8_UNORM_SRGB;
		desc.Width = sizeW;
		desc.Height = sizeH;
		desc.MipLevels = 1;
		desc.SampleCount = 1;
		desc.MiscFlags = ovrTextureMisc_DX_Typeless;
		desc.BindFlags = ovrTextureBind_DX_RenderTarget;
		desc.StaticImage = ovrFalse;

		ovrResult result = ovr_CreateTextureSwapChainDX(session, G_GAPIContext.GetDevice(), &desc, &m_TextureChain);
		if (!OVR_SUCCESS(result))
			return false;

		int textureCount = 0;
		ovr_GetTextureSwapChainLength(m_Session, m_TextureChain, &textureCount);
		for (int i = 0; i < textureCount; ++i)
		{
			ID3D11Texture2D* tex = nullptr;
			ovr_GetTextureSwapChainBufferDX(m_Session, m_TextureChain, i, IID_PPV_ARGS(&tex));
			D3D11_RENDER_TARGET_VIEW_DESC rtvd = {};
			rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			ID3D11RenderTargetView* rtv;
			G_GAPIContext.GetDevice()->CreateRenderTargetView(tex, &rtvd, &rtv);
			m_RenderTargetViews.push_back(rtv);
			tex->Release();
		}

		return true;
	}

	OculusTextureD3D::~OculusTextureD3D()
	{
		for (int i = 0; i < m_RenderTargetViews.size(); ++i)
		{
			m_RenderTargetViews[i]->Release();
		}
		if (m_TextureChain)
		{
			ovr_DestroyTextureSwapChain(m_Session, m_TextureChain);
		}
	}

	ID3D11RenderTargetView* OculusTextureD3D::GetRenderTargetView()
	{
		int index = 0;
		ovr_GetTextureSwapChainCurrentIndex(m_Session, m_TextureChain, &index);
		return m_RenderTargetViews[index];
	}

	ovrTextureSwapChain OculusTextureD3D::GetOvrTextureChain() const noexcept
	{
		return m_TextureChain;
	}

	// Commit changes
	void OculusTextureD3D::Commit() const
	{
		ovr_CommitTextureSwapChain(m_Session, m_TextureChain);
	}
}

#endif