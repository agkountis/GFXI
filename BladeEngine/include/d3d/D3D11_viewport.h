#ifndef BLADE_D3D11_VIEWPORT_H_
#define BLADE_D3D11_VIEWPORT_H_
#include "abstract_viewport.h"

namespace Blade
{
	/**
	 * \brief D3D11 implementation of the AbstractViewport.
	 */
	class D3D11Viewport : public AbstractViewport
	{
	private:
		/**
		 * \brief Minimum depth value of the depth buffer.
		 */
		float m_MinDepth{ 0.0f };

		/**
		 * \brief Maximum depth value of the depth buffer.
		 */
		float m_MaxDepth{ 1.0f };

	public:
		/**
		 * \brief D3D11Viewport default constructor.
		 */
		D3D11Viewport() = default;

		/**
		 * \brief D3D11Viewport constructor.
		 * \param rect The dimensions of the viewport.
		 * \param minDepth The minimum value of the depth buffer.
		 * \param maxDepth The maximum value of the depth buffer.
		 */
		D3D11Viewport(const Recti& rect, float minDepth, float maxDepth)
			: AbstractViewport{ rect },
			  m_MinDepth{ minDepth },
			  m_MaxDepth{ maxDepth }
		{
		}

		void Set() const noexcept override;
	};
}

#endif //BLADE_D3D11_VIEWPORT_H_
