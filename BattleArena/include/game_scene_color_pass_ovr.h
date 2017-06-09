#ifndef GAME_SCENE_COLOR_PASS_OVR_H_
#define GAME_SCENE_COLOR_PASS_OVR_H_
#include <OVR/OVR_CAPI.h>
#include "render_pass.h"
#include "viewport.h"

struct OvrData
{
	ovrSession session;
	ovrGraphicsLuid graphicsLuid;
	ovrHmdDesc hmdDesc;
	ovrSizei eyeResolution[2];
	ovrEyeRenderDesc eyeRenderDesc[2];
	ovrVector3f hmdToEyeViewOffset[2];
	ovrPosef eyePoses[2];
	ovrLayerEyeFov layer;
	ovrTextureSwapChain textureSwapChain;
	ovrTextureSwapChainDesc textureSwapChainDesc;
	ovrMirrorTexture mirrorTexture;
	ovrMirrorTextureDesc mirrorTextureDesc;
	ovrViewScaleDesc viewScaleDesc;
};

struct OvrXformData
{
	Blade::Mat4f view;
	Blade::Mat4f projection;
	Blade::Viewport viewport;
};

class GameSceneColorPassStageOvr : public Blade::RenderPassStage
{
private:
	Blade::D3D11RenderTarget m_ColorRenderTarget;

	OvrData m_OvrData;
	OvrXformData m_OvrXformData;

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

	bool InitializeOvr() noexcept;
	void ShutdownOvr() noexcept;
	bool InitializeOvrData() noexcept;
	void CalculateEyePoses() noexcept;
	const OvrXformData& GetOvrXformDataPerEye(ovrEyeType eye) noexcept;

public:
	GameSceneColorPassStageOvr(const std::string& name);

	bool Initialize() override;

	Blade::PipelineData<Blade::D3D11RenderTarget*> Execute(const std::vector<Blade::RenderComponent*>& data, const Blade::PipelineData<Blade::D3D11RenderTarget*>& tdata) noexcept override;
};

#endif //GAME_SCENE_COLOR_PASS_OVR_H_
