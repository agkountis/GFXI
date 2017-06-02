#include "material.h"

namespace Blade
{
	Material::Material() : blendState{ RenderStateType::BS_BLEND_DISSABLED }
	{
		for (int i = 0; i < SUPPORTED_TEX_COUNT; ++i)
		{
			textures[i] = nullptr;
		}
	}
}
