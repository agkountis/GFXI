#include "abstract_viewport.h"

namespace Blade
{
	const Recti& AbstractViewport::GetRect() const noexcept
	{
		return m_Rect;
	}

	void AbstractViewport::SetRect(const Recti& rect) noexcept
	{
		m_Rect = rect;
	}
}
