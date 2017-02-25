#ifndef BATTLE_ARENA_GAME_SCENE_COLOR_PASS_STAGE_H_
#define BATTLE_ARENA_GAME_SCENE_COLOR_PASS_STAGE_H_
#include "render_pass.h"
#include "d3d/D3D11_render_target.h"

class GameSceneColorPassStage : public Blade::RenderPassStage
{
private:
	Blade::D3D11RenderTarget m_ColorRenderTarget;

	Blade::ComPtr<ID3D11SamplerState> m_SamplerLinearWrap;

	void DisplayToScreen() const;

public:
	GameSceneColorPassStage(const std::string& name)
		: Blade::RenderPassStage{ name }
	{
	}

	bool Initialize() override;

	Blade::PipelineData<Blade::D3D11RenderTarget*> Execute(const std::vector<Blade::RenderComponent*>& data,
	                                                       const Blade::PipelineData<Blade::D3D11RenderTarget*>& tdata) noexcept override;
};

#endif //BATTLE_ARENA_GAME_SCENE_COLOR_PASS_STAGE_H_
