#ifndef BLADE_VERTEX_H_
#define BLADE_VERTEX_H_

#include "types.h"

namespace Blade
{
	/*
	\brief Vertex struct of the engine.
	*/
	struct Vertex
	{
		Vec3f position;
		Vec3f normal;
		Vec3f tangent;
		Vec2f texcoord;
		Vec4f color;

		Vertex() = default;

		Vertex(const Vec3f& p,
		       const Vec3f& n,
		       const Vec3f& tan,
		       const Vec2f& tcoord,
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
