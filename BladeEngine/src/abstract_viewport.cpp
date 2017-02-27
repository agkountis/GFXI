#include "abstract_viewport.h"

namespace Blade
{
	const Rect& AbstractViewport::GetRect() const noexcept
	{
		return m_Rect;
	}

	void AbstractViewport::SetRect(const Rect& rect) noexcept
	{
		m_Rect = rect;
	}
}
