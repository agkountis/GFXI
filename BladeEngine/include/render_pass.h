#ifndef BLADE_RENDER_PASS_H_
#define BLADE_RENDER_PASS_H_
#include <vector>
#include "render_component.h"
#include "pipeline_stage.h"
#include "d3d/D3D11_render_target.h"

namespace Blade
{
#if defined(BLADE_BUILD_D3D)
	/**
	 * \brief Type alias of a PipelineStage indicating a render pass pipeline stage.
	 */
	using RenderPassStage = PipelineStage<RenderComponent*, D3D11RenderTarget*>;
#else
#endif
}

#endif //BLADE_RENDER_PASS_H_
