#ifndef BLADE_MATERIAL_H_
#define BLADE_MATERIAL_H_
#include "texture.h"
#include "types.h"
#include "render_state.h"
#include <array>

namespace Blade
{
	struct Material
	{
		std::array<Texture*, SUPPORTED_TEX_COUNT> textures;
		Vec4f diffuse;
		Vec4f specular;
		Mat4f textureMatrix;
		std::string shaderProgramName{ "sdrprog_default" };
		RenderStateType blendState;

		Material();

		Material(const Material& other) = default;
		Material& operator=(const Material& other) = default;
	};
}

#endif //BLADE_MATERIAL_H_
