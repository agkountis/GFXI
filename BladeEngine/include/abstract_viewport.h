#ifndef BLADE_ABSTRACT_VIEWPORT_H_
#define BLADE_ABSTRACT_VIEWPORT_H_
#include "types.h"

namespace Blade
{
	using Rect = Vec4i;

	class AbstractViewport
	{
	private:
		Rect m_Rect;

	public:
		AbstractViewport() = default;

		explicit AbstractViewport(const Rect& rect)
			: m_Rect{ rect }
		{
		}

		virtual ~AbstractViewport() = default;

		const Rect& GetRect() const noexcept;

		void SetRect(const Rect& rect) noexcept;

		virtual void Set() const noexcept = 0;
	};
}

#endif //BLADE_ABSTRACT_VIEWPORT_H_
