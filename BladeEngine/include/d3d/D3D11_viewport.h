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
		float m_MinDepth{ 0.0f };
		float m_MaxDepth{ 1.0f };

	public:
		D3D11Viewport() = default;

		D3D11Viewport(const Rect& rect, float minDepth, float maxDepth)
			: AbstractViewport{ rect },
			  m_MinDepth{ minDepth },
			  m_MaxDepth{ maxDepth }
		{
		}

		void Set() const noexcept override;
	};
}

#endif //BLADE_D3D11_VIEWPORT_H_
