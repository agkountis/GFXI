#ifndef BLADE_ABSTRACT_VIEWPORT_H_
#define BLADE_ABSTRACT_VIEWPORT_H_
#include "types.h"

namespace Blade
{
	/**
	 * \brief Type alias of a Vec4i.
	 */
	using Rect = Vec4i;

	/**
	 * \brief Describes an implementation agnostic Viewport.
	 */
	class AbstractViewport
	{
	private:
		/**
		 * \brief The dimensions of the viewport.
		 */
		Rect m_Rect;

	public:
		/**
		 * \brief AbstractViewport's default constructor.
		 */
		AbstractViewport() = default;

		/**
		 * \brief AbstractViewport's constructor.
		 * \param rect The dimensions of the Viewport.
		 */
		explicit AbstractViewport(const Rect& rect)
			: m_Rect{ rect }
		{
		}

		/**
		 * \brief AbstractViewport's default destructor.
		 */
		virtual ~AbstractViewport() = default;

		/**
		 * \brief Provides the dimensions of the Viewport.
		 * \return The dimensions of the Viewport.
		 */
		const Rect& GetRect() const noexcept;

		/**
		 * \brief Sets the dimensions of the Viewport.
		 * \param rect The dimensions of the Viewport.
		 */
		void SetRect(const Rect& rect) noexcept;

		/**
		 * \brief Sets the Viewport to the Rasterizer.
		 */
		virtual void Set() const noexcept = 0;
	};
}

#endif //BLADE_ABSTRACT_VIEWPORT_H_
