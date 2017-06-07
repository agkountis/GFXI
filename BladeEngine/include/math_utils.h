#ifndef BLADE_MATH_UTILS_H_
#define BLADE_MATH_UTILS_H_
#include "types.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtx/spline.hpp"

namespace Blade
{
	namespace MathUtils
	{
		constexpr float PI_F{ glm::pi<float>() };

		constexpr double PI_D{ glm::pi<double>() };

		static Mat4f identityMatrix{ glm::mat4{ 1.0f } };

		inline float RandomRange(float l, float h) noexcept
		{
			return l + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (h - l)));
		}

		inline Vec2f Normalize(const Vec2f& vec) noexcept
		{
			return glm::normalize(vec);
		}

		inline Vec3f Normalize(const Vec3f& vec) noexcept
		{
			return glm::normalize(vec);
		}

		inline Vec4f Normalize(const Vec4f& vec) noexcept
		{
			return glm::normalize(vec);
		}

		inline Quatf Normalize(const Quatf& q) noexcept
		{
			return glm::normalize(q);
		}

		inline float Lengthf(const Vec2f& vec) noexcept
		{
			return glm::length(vec);
		}

		inline float Lengthf(const Vec3f& vec) noexcept
		{
			return glm::length(vec);
		}

		inline float Lengthf(const Vec4f& vec) noexcept
		{
			return glm::length(vec);
		}

		inline double Lengthd(const Vec2d& vec) noexcept
		{
			return glm::length(vec);
		}

		inline double Lengthd(const Vec3f& vec) noexcept
		{
			return glm::length(vec);
		}

		inline double Lengthd(const Vec4d& vec) noexcept
		{
			return glm::length(vec);
		}

		inline Mat4f Transpose(const Mat4f& mat) noexcept
		{
			return glm::transpose(mat);
		}

		inline Mat4f Inverse(const Mat4f& mat) noexcept
		{
			return glm::inverse(mat);
		}

		inline Mat4f Translate(const Mat4f& matrix, const Vec3f& vector) noexcept
		{
			return glm::translate(matrix, vector);
		}

		inline Mat4f Rotate(const Mat4f& matrix, float angle, const Vec3f& axis) noexcept
		{
			return glm::rotate(matrix, angle, axis);
		}

		inline Mat4f Rotate(const Mat4f& matrix, const Quatf& orientation) noexcept
		{
			return matrix * glm::toMat4(orientation);
		}

		inline Quatf Rotate(const Quatf& q, float angle, const Vec3f& axis) noexcept
		{
			Quatf res = glm::rotate(q, angle, axis);
			return res;
		}

		inline Mat4f Scale(const Mat4f& matrix, const Vec3f& scale) noexcept
		{
			return glm::scale(matrix, scale);
		}

		inline Mat4f PerspectiveLH(float fov, float width, float height, float near_plane, float far_plane) noexcept
		{
			return glm::perspectiveFovLH(fov, width, height, near_plane, far_plane);
		}

		inline Vec3f SphericalToCartesian(float theta, float phi, float radius = 1.0f) noexcept
		{
			return Vec3f{ radius * sin(theta) * sin(phi), radius * cos(phi), radius * cos(theta) * sin(phi) };
		}

		inline Mat4f LookatLH(const Vec3f& position, const Vec3f& target, const Vec3f& up) noexcept
		{
			return glm::lookAtLH(position, target, up);
		}

		inline Vec3f CatmullRom(const Vec3f& a, const Vec3f& b, const Vec3f& c, const Vec3f& d, float t) noexcept
		{
			return glm::catmullRom(a, b, c, d, t);
		}

		inline float Lerp(float a, float b, float t) noexcept
		{
			return glm::mix(a, b, t);
		}

		inline Vec3f Lerp(const Vec3f& a, const Vec3f& b, float t) noexcept
		{
			return glm::mix(a, b, t);
		}

		inline Vec3f Lerp(const Vec3f& a, const Vec3f& b, const Vec3f& t) noexcept
		{
			return glm::mix(a, b, t);
		}

		inline Vec4f Lerp(const Vec4f& a, const Vec4f& b, float t) noexcept
		{
			return glm::mix(a, b, t);
		}

		inline Vec4f Lerp(const Vec4f& a, const Vec4f& b, const Vec4f& t) noexcept
		{
			return glm::mix(a, b, t);
		}

		inline Quatf Lerp(const Quatf& a, const Quatf& b, float t) noexcept
		{
			return glm::mix(a, b, t);
		}

		inline Quatf Slerp(const Quatf& a, const Quatf& b, float t) noexcept
		{
			return glm::slerp(a, b, t);
		}

		inline float Dotf(const Vec3f& a, const Vec3f& b) noexcept
		{
			return glm::dot(a, b);
		}

		inline Vec3f Cross(const Vec3f& a, const Vec3f& b) noexcept
		{
			return glm::cross(a, b);
		}

		template <typename T>
		T ToRadians(T degrees) noexcept
		{
			return glm::radians(degrees);
		}

		template <typename T>
		T ToDegrees(T radians) noexcept
		{
			return glm::degrees(radians);
		}


		struct State
		{
			float x{ 0.0f };
			float v{ 0.0f };
			float force{ 0.0f };
			float mass{ 0.0f };
		};

		struct Derivative
		{
			float dx{ 0.0f };
			float dv{ 0.0f };
		};

		/*
		\brief RungKutta4Integrator is an helper class to integrate simulation states.
		*/
		class RungeKutta4Integrator
		{
		private:
			static Derivative Evaluate(const State& initial, float timeSec, float deltaTime, const Derivative& derivative) noexcept;

			static State Integrate(const State& state, float timeSec, float deltaTime) noexcept;

		public:
			static void Integrate(Vec3f& position, Vec3f& velocity, const Vec3f& force, float mass, float timeSec, float deltaTime) noexcept;
		};

	}
}

#endif //BLADE_MATH_UTILS_H_
