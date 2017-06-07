#include "particles_render_pass.h"
#include "math_utils.h"
#include "emitter_component.h"
using namespace Blade;

struct ParticleUniformBuffer
{
	Mat4f MVP;
	Vec4f diffuse;
};

void ParticleRenderPassStage::DisplayToScreen() const
{
}

ParticleRenderPassStage::ParticleRenderPassStage(const std::string& name)
	: RenderPassStage{name}
{

}

bool ParticleRenderPassStage::Initialize()
{
	/*
	Port old code here
	*/
}

PipelineData<Blade::D3D11RenderTarget*> ParticleRenderPassStage::Execute(const std::vector<RenderComponent*>& data, const Blade::PipelineData<Blade::D3D11RenderTarget*>& tData) noexcept
{
	/*
	Port other code here 
	*/
}
