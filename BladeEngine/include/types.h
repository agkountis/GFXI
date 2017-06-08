#ifndef BLADE_TYPES_H_
#define BLADE_TYPES_H_

#include "GLM/glm.hpp"
#include "GLM/gtx/quaternion.hpp"
#include "wrl.h"
#include "message.h"
#include "ref_counted_container.h"

//#ifdef _DEBUG
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif

namespace Blade
{
	using Vec2i = glm::ivec2;
	using Vec3i = glm::ivec3;
	using Vec4i = glm::ivec4;

	using Vec2ui = glm::uvec2;
	using Vec3ui = glm::uvec3;
	using Vec4ui = glm::uvec4;

	using Vec2f = glm::vec2;
	using Vec3f = glm::vec3;
	using Vec4f = glm::vec4;

	using Vec2d = glm::dvec2;
	using Vec3d = glm::dvec3;
	using Vec4d = glm::dvec4;

	using Mat2f = glm::mat2;
	using Mat3f = glm::mat3;
	using Mat4f = glm::mat4;

	using Mat2d = glm::dmat2;
	using Mat3d = glm::dmat3;
	using Mat4d = glm::dmat4;

	using Quatf = glm::quat;
	using Quatd = glm::dquat;

	using Byte = char;

	template <typename T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	template<typename T>
	using MessageContainer = RefCountedContainer<Message<T>>;
}


#endif //BLADE_TYPES_H_
