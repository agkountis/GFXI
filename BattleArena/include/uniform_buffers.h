#ifndef UNIFORM_BUFFERS_H_
#define UNIFORM_BUFFERS_H_
#include "types.h"

struct UniformBuffer
{
	Blade::Mat4f MVP;
	Blade::Mat4f ITMV;
	Blade::Mat4f MV;
	Blade::Mat4f V;
	Blade::Mat4f textureMatrix;
	Blade::Vec4f diffuse;
	Blade::Vec4f specular;
	int pointLightCount;
	int directionalLightCount;
	int spotlightCount;
	float pad;
};

struct ParticleUniformBuffer
{
	Blade::Mat4f MVP;
	Blade::Vec4f diffuse;
};

#endif //UNIFORM_BUFFERS_H_
