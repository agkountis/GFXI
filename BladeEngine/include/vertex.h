#ifndef BLADE_VERTEX_H_
#define BLADE_VERTEX_H_

#include "types.h"

namespace Blade
{
	struct Vertex
	{
		Vec4f position{ 0.0f, 0.0f, 0.0f, 1.0f };
		Vec4f normal;
		Vec4f tangent;
		Vec4f texcoord;
		Vec4f color;

		Vertex() = default;

		Vertex(const Vec4f& p,
		       const Vec4f& n,
		       const Vec4f& tan,
		       const Vec4f& tcoord,
		       const Vec4f& col) : position{ p },
		                           normal{ n },
		                           tangent{ tan },
		                           texcoord{ tcoord },
		                           color{ col }
		{
		}
	};
}

#endif //BLADE_VERTEX_H_
