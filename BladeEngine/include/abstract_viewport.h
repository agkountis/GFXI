#ifndef BLADE_ABSTRACT_VIEWPORT_H_
#define BLADE_ABSTRACT_VIEWPORT_H_
#include "types.h"

namespace Blade
{
	/**
	 * \brief Type alias of a Vec4i.
	 */
	using Recti = Vec4i;

	/**
	 * \brief Describes an implementation agnostic Viewport.
	 */
	class AbstractViewport
	{
	private:
		/**
		 * \brief The dimensions of the viewport.
		 */
		Recti m_Rect;

	public:
		/**
		 * \brief AbstractViewport's default constructor.
		 */
		AbstractViewport() = default;

		/**
		 * \brief AbstractViewport's constructor.
		 * \param rect The dimensions of the Viewport.
		 */
		explicit AbstractViewport(const Recti& rect)
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
		const Recti& GetRect() const noexcept;

		/**
		 * \brief Sets the dimensions of the Viewport.
		 * \param rect The dimensions of the Viewport.
		 */
		void SetRect(const Recti& rect) noexcept;

		/**
		 * \brief Sets the Viewport to the Rasterizer.
		 */
		virtual void Set() const noexcept = 0;
	};
}

#endif //BLADE_ABSTRACT_VIEWPORT_H_
