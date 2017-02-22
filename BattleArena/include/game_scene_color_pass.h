#ifndef BATTLE_ARENA_GAME_SCENE_COLOR_PASS_H_
#define BATTLE_ARENA_GAME_SCENE_COLOR_PASS_H_
#include "render_pass.h"
#include "d3d/D3D11_render_target.h"

class GameSceneColorPass : public Blade::RenderPass
{
private:
	Blade::D3D11RenderTarget m_ColorRenderTarget;

	Blade::ComPtr<ID3D11SamplerState> m_SamplerLinearWrap;

	void DisplayToScreen() const;

public:
	GameSceneColorPass(const std::string& name)
		: RenderPass{ name }
	{
	}

	bool Initialize() override;

	void Execute(const std::vector<Blade::RenderComponent*>& renderComponents) const noexcept override;
};

#endif //BATTLE_ARENA_GAME_SCENE_COLOR_PASS_H_
