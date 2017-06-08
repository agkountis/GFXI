#ifndef BLADE_ANIMATION_H_
#define BLADE_ANIMATION_H_
#include "types.h"
#include <string>
#include <vector>

namespace Blade
{
	template <typename T>
	struct Keyframe
	{
		T value;
		long time{ 0 };

		Keyframe<T>() = default;

		Keyframe<T>(const T& value, long time)
			: value{ value },
			  time{ time }
		{
		}

		bool operator<(const Keyframe<T>& other) const noexcept
		{
			return time < other.time;
		}
	};

	using KeyframeVec3f = Keyframe<Vec3f>;

	using KeyframeQuatf = Keyframe<Quatf>;

	class Animation
	{
	private:
		std::string m_Name;

		std::vector<KeyframeVec3f> m_PositionKeyframes;

		std::vector<KeyframeQuatf> m_RotationKeyframes;

		std::vector<KeyframeVec3f> m_ScalingKeyframes;

		bool m_Loop;

		float m_AnimationSpeed;

	public:
		Animation();

		Animation(const std::string& name, bool loopState);

		void SetName(const std::string &name);
		void SetLoopping(bool loopState);

		const std::string& GetName() const noexcept;

		const KeyframeVec3f& GetPositionKeyframe(unsigned int idx) const noexcept;
		const KeyframeQuatf& GetRotationKeyframe(unsigned int idx) const noexcept;
		const KeyframeVec3f& GetScalingKeyframe(unsigned int idx) const noexcept;

		size_t GetPositionKeyframeCount() const noexcept;
		size_t GetRotationKeyframeCount() const noexcept;
		size_t GetScalingKeyframeCount() const noexcept;

		void SetAnimationSpeed(float speed) noexcept;
		float GetAnimationSpeed() const noexcept;

		bool HasPositionKeyframes() const noexcept;
		bool HasRotationKeyframes() const noexcept;
		bool HasScalingKeyframes() const noexcept;
		bool DoesLoop() const noexcept;

		void AddPositionKeyframe(const KeyframeVec3f &pos) noexcept;
		void AddRotationKeyframe(const KeyframeQuatf &rot) noexcept;
		void AddScalingKeyframe(const KeyframeVec3f &scaling) noexcept;

		void ReplacePositionKeyframe(const KeyframeVec3f &pos, unsigned int idx) noexcept;
		void ReplaceRotationKeyframe(const KeyframeQuatf&rot, unsigned int idx) noexcept;
		void ReplaceScalingKeyframe(const KeyframeVec3f &scaling, unsigned int idx) noexcept;

		void ClearKeyframes() noexcept;

		void SortPositionKeyframes() noexcept;
		void SortRotationKeyframes() noexcept;
		void SortScalingKeyframes() noexcept;
	};
}

#endif
