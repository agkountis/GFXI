#ifndef GAME_SCENE_COLOR_PASS_OVR_H_
#define GAME_SCENE_COLOR_PASS_OVR_H_

#ifdef BLADE_BUILD_OVR

#include "render_pass.h"
#include "engine_context.h"


class GameSceneColorPassStageOvr : public Blade::RenderPassStage
{
private:
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

	float m_Brightness{ 1.0f };

public:
	float scale{ 1.0f };

	explicit GameSceneColorPassStageOvr(const std::string& name);

	bool Initialize() override;

	void UpdateBrightness(float brightness) noexcept;

	Blade::PipelineData<Blade::D3D11RenderTarget*> Execute(const std::vector<Blade::RenderComponent*>& data, const Blade::PipelineData<Blade::D3D11RenderTarget*>& tdata) noexcept override;
};

#endif //BLADE_BUILD_OVR

#endif //GAME_SCENE_COLOR_PASS_OVR_H_
