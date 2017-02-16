#ifndef BLADE_RENDER_TARGET_H_
#define BLADE_RENDER_TARGET_H_
#include "types.h"

namespace Blade
{
	enum class RenderTargetBindType
	{
		COLOR_AND_DEPTH,
		DEPTH
	};

	class RenderTarget
	{
	private:
		Vec2i m_Size;

	public:
		RenderTarget() = default;

		explicit RenderTarget(const Vec2i& size) : m_Size{ size }
		{
		}

		virtual ~RenderTarget();

		virtual bool Create(const Vec2i& size) = 0;

		virtual bool Bind(RenderTargetBindType bind_type) const = 0;

		virtual bool Unbind() const = 0;

		void SetSize(const Vec2i& size) noexcept
		{
			m_Size = size;
		}

		const Vec2i& GetSize() const noexcept
		{
			return m_Size;
		}
	};
}

#endif //GLACIER_ENGINE_RENDER_TARGET_H_
