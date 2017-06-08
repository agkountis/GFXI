#ifndef BLADE_MATERIAL_H_
#define BLADE_MATERIAL_H_
#include "texture.h"
#include "types.h"
#include "render_state.h"
#include <array>

namespace Blade
{
	/*
	\brief Material struct of the engine
	*/
	struct Material
	{
		/*
		\brief The array of textures of the material
		*/
		std::array<Texture*, SUPPORTED_TEX_COUNT> textures;
		/*
		\brief Diffuse component of the material.
		*/
		Vec4f diffuse;
		/*
		\brief Specular component of the material.
		*/
		Vec4f specular;
		/*
		\brief The texture matrix transformation.
		*/
		Mat4f textureMatrix;
		/*
		\brief The shader program name that need to used to render this material
		*/
		std::string shaderProgramName{ "sdrprog_default" };

		/*
		\brief Blend state of the material
		*/
		RenderStateType blendState;

		Material();

		Material(const Material& other) = default;
		Material& operator=(const Material& other) = default;
	};
}

#endif //BLADE_MATERIAL_H_
