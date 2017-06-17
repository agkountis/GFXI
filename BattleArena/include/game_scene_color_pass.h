#ifndef GAME_SCENE_COLOR_PASS_STAGE_H_
#define GAME_SCENE_COLOR_PASS_STAGE_H_
#include "render_pass.h"
#include "d3d/D3D11_render_target.h"
#include "texture.h"

class GameSceneColorPassStage : public Blade::RenderPassStage
{
private:
	Blade::D3D11RenderTarget m_ColorRenderTarget;

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

	void DisplayToScreen() const;


public:
	GameSceneColorPassStage(const std::string& name)
		: Blade::RenderPassStage{ name }
	{
	}

	bool Initialize() override;

	Blade::PipelineData<Blade::D3D11RenderTarget*> Execute(const std::vector<Blade::RenderComponent*>& data,
	                                                       const Blade::PipelineData<Blade::D3D11RenderTarget*>& tdata) noexcept override;
	void SetBrightness(float brightness);

};

#endif //BATTLE_ARENA_GAME_SCENE_COLOR_PASS_STAGE_H_
