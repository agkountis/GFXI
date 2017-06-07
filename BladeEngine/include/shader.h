#ifndef BLADE_SHADER_H_
#define BLADE_SHADER_H_
#include "resource.h"

namespace Blade
{
	/*
	\brief Shader type enum of the engine.
	*/
	enum ShaderType
	{
		VERTEX_SHADER,
		HULL_SHADER,
		DOMAIN_SHADER,
		GEOMETRY_SHADER,
		FRAGMENT_SHADER,
		SHADER_COUNT
	};

	/*
	\brief Shader class of the engine.
	*/
	class Shader : public Resource
	{
	public:
		Shader() = default;
	};
}

#endif //BLADE_SHADER_H_
