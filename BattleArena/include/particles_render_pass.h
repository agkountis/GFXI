#ifndef BATTLE_ARENA_PARTICLES_RENDER_PASS_STAGE_H_
#define BATTLE_ARENA_PARTICLES_RENDER_PASS_STAGE_H_
#include "render_pass.h"
#include "d3d/D3D11_render_target.h"

class ParticleRenderPassStage : public Blade::RenderPassStage
{
private:
	//render target, samplers, buffers here

	void DisplayToScreen() const;

public:

	ParticleRenderPassStage(const std::string& name);

	bool Initialize() override;

	Blade::PipelineData<Blade::D3D11RenderTarget*> Execute(const std::vector<Blade::RenderComponent*>& data,
		const Blade::PipelineData<Blade::D3D11RenderTarget*>& tData) noexcept override;

private:

};


#endif