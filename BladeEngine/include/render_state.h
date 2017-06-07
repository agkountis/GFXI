#ifndef BLADE_RENDER_STATE_H_
#define BLADE_RENDER_STATE_H_

namespace Blade
{
	enum class RenderStateType
	{
		BS_BLEND_DISSABLED,
		BS_BLEND_ADDITIVE,
		BS_BLEND_ALPHA,
		RS_CULL_FRONT,
		RS_CULL_BACK,
		RS_DRAW_WIRE,
		RS_DRAW_SOLID,
		DSS_DEPTH_MASK_0,
		DSS_DEPTH_MASK_1,
		DSS_DEPTH_TEST_DISABLE,
		DSS_DEPTH_TEST_ENABLE
	};

	/*
	\brief Render state of the engine.
	*/
	class RenderState
	{
	public:
		RenderState() = default;

		virtual ~RenderState();

		virtual void Set() const noexcept = 0;
	};
}

#endif //BLADE_RENDER_STATE_H_
