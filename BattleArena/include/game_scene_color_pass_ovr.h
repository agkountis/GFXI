#ifndef GAME_SCENE_COLOR_PASS_OVR_H_
#define GAME_SCENE_COLOR_PASS_OVR_H_
#include "render_pass.h"
#include "engine_context.h"
#include <OVR/OVR_CAPI_D3D.h>

struct OculusTexture
{
	ovrSession               Session;
	ovrTextureSwapChain      TextureChain;
	std::vector<ID3D11RenderTargetView*> TexRtv;

	OculusTexture() :
		Session(nullptr),
		TextureChain(nullptr)
	{
	}

	bool Init(ovrSession session, int sizeW, int sizeH)
	{
		Session = session;

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

		ovrResult result = ovr_CreateTextureSwapChainDX(session, Blade::EngineContext::GetGAPIContext().GetDevice(), &desc, &TextureChain);
		if (!OVR_SUCCESS(result))
			return false;

		int textureCount = 0;
		ovr_GetTextureSwapChainLength(Session, TextureChain, &textureCount);
		for (int i = 0; i < textureCount; ++i)
		{
			ID3D11Texture2D* tex = nullptr;
			ovr_GetTextureSwapChainBufferDX(Session, TextureChain, i, IID_PPV_ARGS(&tex));
			D3D11_RENDER_TARGET_VIEW_DESC rtvd = {};
			rtvd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			ID3D11RenderTargetView* rtv;
			Blade::EngineContext::GetGAPIContext().GetDevice()->CreateRenderTargetView(tex, &rtvd, &rtv);
			TexRtv.push_back(rtv);
			tex->Release();
		}

		return true;
	}

	~OculusTexture()
	{
		for (int i = 0; i < TexRtv.size(); ++i)
		{
			TexRtv[i]->Release();
		}
		if (TextureChain)
		{
			ovr_DestroyTextureSwapChain(Session, TextureChain);
		}
	}

	ID3D11RenderTargetView* GetRTV()
	{
		int index = 0;
		ovr_GetTextureSwapChainCurrentIndex(Session, TextureChain, &index);
		return TexRtv[index];
	}

	// Commit changes
	void Commit() const
	{
		ovr_CommitTextureSwapChain(Session, TextureChain);
	}
};

struct DepthBuffer
{
	ID3D11DepthStencilView * TexDsv;

	DepthBuffer(ID3D11Device * Device, int sizeW, int sizeH, int sampleCount = 1)
	{
		DXGI_FORMAT format = DXGI_FORMAT_D32_FLOAT;
		D3D11_TEXTURE2D_DESC dsDesc;
		dsDesc.Width = sizeW;
		dsDesc.Height = sizeH;
		dsDesc.MipLevels = 1;
		dsDesc.ArraySize = 1;
		dsDesc.Format = format;
		dsDesc.SampleDesc.Count = sampleCount;
		dsDesc.SampleDesc.Quality = 0;
		dsDesc.Usage = D3D11_USAGE_DEFAULT;
		dsDesc.CPUAccessFlags = 0;
		dsDesc.MiscFlags = 0;
		dsDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		ID3D11Texture2D * Tex;
		Device->CreateTexture2D(&dsDesc, nullptr, &Tex);
		Device->CreateDepthStencilView(Tex, nullptr, &TexDsv);
		Tex->Release();
	}

	~DepthBuffer()
	{
		if(TexDsv)
		{
			TexDsv->Release();
		}
	}
};

class GameSceneColorPassStageOvr : public Blade::RenderPassStage
{
private:
	std::vector<ID3D11RenderTargetView*> m_ColorRenderTargets;
	ID3D11DepthStencilView* m_DepthStencilView{ nullptr };

	int m_CurrentRenderTargetIndex;

	Blade::ComPtr<ID3D11Texture2D> m_MirrorTexture;

	Blade::ComPtr<ID3D11SamplerState> m_SamplerLinearWrap;

	Blade::ComPtr<ID3D11Buffer> m_ConstantBuffer;

	Blade::ComPtr<ID3D11Buffer> m_ParticleBuffer;

	Blade::ComPtr<ID3D11Buffer> m_PointLightStructuredBuffer;
	Blade::ComPtr<ID3D11ShaderResourceView> m_PointLightSrv;

	Blade::ComPtr<ID3D11Buffer> m_DirectionalLightStructuredBuffer;
	Blade::ComPtr<ID3D11ShaderResourceView> m_DirectionalLightSrv;

	Blade::ComPtr<ID3D11Buffer> m_SpotlightStructuredBuffer;
	Blade::ComPtr<ID3D11ShaderResourceView> m_SpotlightSrv;

	Blade::Texture* m_DummyDiff{ nullptr };
	Blade::Texture* m_DummySpec{ nullptr };
	Blade::Texture* m_DummyNorm{ nullptr };


public:
	GameSceneColorPassStageOvr(const std::string& name);

	bool Initialize() override;

	Blade::PipelineData<Blade::D3D11RenderTarget*> Execute(const std::vector<Blade::RenderComponent*>& data, const Blade::PipelineData<Blade::D3D11RenderTarget*>& tdata) noexcept override;
};

#endif //GAME_SCENE_COLOR_PASS_OVR_H_
