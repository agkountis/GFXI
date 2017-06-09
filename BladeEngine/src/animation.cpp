#include "animation.h"
#include "trace.h"
#include <algorithm>

namespace Blade
{
	Animation::Animation()
		: m_Loop{ true },
		  m_AnimationSpeed{ 1.0f }
	{
		m_PositionKeyframes.push_back(KeyframeVec3f{});

		m_RotationKeyframes.push_back(KeyframeQuatf{});

		m_ScalingKeyframes.push_back(KeyframeVec3f{ Vec3f{ 1.0f, 1.0f, 1.0f }, 0 });
	}

	Animation::Animation(const std::string& name, bool loopState)
		: m_Name{ name },
		  m_Loop{ loopState },
		  m_AnimationSpeed{ 1.0f }
	{
		m_PositionKeyframes.push_back(KeyframeVec3f{});

		m_RotationKeyframes.push_back(KeyframeQuatf{});

		m_ScalingKeyframes.push_back(KeyframeVec3f{ Vec3f{ 1.0f, 1.0f, 1.0f }, 0 });
	}

	void Animation::SetName(const std::string& name)
	{
		m_Name = name;
	}

	void Animation::SetLoopping(bool loopState)
	{
		m_Loop = loopState;
	}

	const std::string& Animation::GetName() const noexcept
	{
		return m_Name;
	}

	const KeyframeVec3f& Animation::GetPositionKeyframe(unsigned idx) const noexcept
	{
		if (idx > m_PositionKeyframes.size())
		{
			BLADE_ERROR("Cannot provide requested position keyframe. Index out of range.");
			BLADE_WARNING("Returning last available position keyframe.");

			return m_PositionKeyframes[m_PositionKeyframes.size() - 1];
		}

		return m_PositionKeyframes[idx];
	}

	const KeyframeQuatf& Animation::GetRotationKeyframe(unsigned idx) const noexcept
	{
		if (idx > m_RotationKeyframes.size())
		{
			BLADE_ERROR("Cannot provide requested rotation keyframe. Index out of range.");
			BLADE_WARNING("Returning last available rotation keyframe.");

			return m_RotationKeyframes[m_RotationKeyframes.size() - 1];
		}

		return m_RotationKeyframes[idx];
	}

	const KeyframeVec3f& Animation::GetScalingKeyframe(unsigned idx) const noexcept
	{
		if (idx > m_ScalingKeyframes.size() - 1)
		{
			BLADE_ERROR("Cannot provide requested scaling keyframe. Index out of range.");
			BLADE_WARNING("Returning last available scaling keyframe.");

			return m_ScalingKeyframes[m_ScalingKeyframes.size() - 1];
		}

		return m_ScalingKeyframes[idx];
	}

	size_t Animation::GetPositionKeyframeCount() const noexcept
	{
		return m_PositionKeyframes.size();
	}

	size_t Animation::GetRotationKeyframeCount() const noexcept
	{
		return m_RotationKeyframes.size();
	}

	size_t Animation::GetScalingKeyframeCount() const noexcept
	{
		return m_ScalingKeyframes.size();
	}

	void Animation::SetAnimationSpeed(float speed) noexcept
	{
		m_AnimationSpeed = speed;
	}

	float Animation::GetAnimationSpeed() const noexcept
	{
		return m_AnimationSpeed;
	}

	bool Animation::HasPositionKeyframes() const noexcept
	{
		return m_PositionKeyframes.empty();
	}

	bool Animation::HasRotationKeyframes() const noexcept
	{
		return m_RotationKeyframes.empty();
	}

	bool Animation::HasScalingKeyframes() const noexcept
	{
		return m_ScalingKeyframes.empty();
	}

	bool Animation::DoesLoop() const noexcept
	{
		return m_Loop;
	}

	void Animation::AddPositionKeyframe(const KeyframeVec3f& pos) noexcept
	{
		auto it = std::find_if(m_PositionKeyframes.begin(), m_PositionKeyframes.end(), [&](auto& keyframe) { return pos.time == keyframe.time; });

		if (it == m_PositionKeyframes.end())
		{
			m_PositionKeyframes.push_back(pos);
		}
		else
		{
			BLADE_WARNING("A position keyframe with the specified timestamp already exists. Replacing");
			*it = pos;
		}
	}

	void Animation::AddRotationKeyframe(const KeyframeQuatf& rot) noexcept
	{
		auto it = std::find_if(m_RotationKeyframes.begin(), m_RotationKeyframes.end(), [&](auto& keyframe) { return rot.time == keyframe.time; });

		if (it == m_RotationKeyframes.end())
		{
			m_RotationKeyframes.push_back(rot);
		}
		else
		{
			BLADE_WARNING("A rotation keyframe with the specified timestamp already exists. Replacing");
			*it = rot;
		}
	}

	void Animation::AddScalingKeyframe(const KeyframeVec3f& scaling) noexcept
	{
		auto it = std::find_if(m_ScalingKeyframes.begin(), m_ScalingKeyframes.end(), [&](auto& keyframe) { return scaling.time == keyframe.time; });

		if (it == m_ScalingKeyframes.end())
		{
			m_ScalingKeyframes.push_back(scaling);
		}
		else
		{
			BLADE_WARNING("A scaling keyframe with the specified timestamp already exists. Replacing");
			*it = scaling;
		}
	}

	void Animation::ReplacePositionKeyframe(const KeyframeVec3f& pos, unsigned idx) noexcept
	{
		if (!idx > m_PositionKeyframes.size() - 1)
		{
			m_PositionKeyframes[idx] = pos;
		}
		else
		{
			BLADE_ERROR("Cannot replace position keyframe. Index out of range.");
		}
	}

	void Animation::ReplaceRotationKeyframe(const KeyframeQuatf& rot, unsigned idx) noexcept
	{
		if (!idx > m_RotationKeyframes.size() - 1)
		{
			m_RotationKeyframes[idx] = rot;
		}
		else
		{
			BLADE_ERROR("Cannot replace rotation keyframe. Index out of range.");
		}
	}

	void Animation::ReplaceScalingKeyframe(const KeyframeVec3f& scaling, unsigned idx) noexcept
	{
		if (!idx > m_ScalingKeyframes.size() - 1)
		{
			m_ScalingKeyframes[idx] = scaling;
		}
		else
		{
			BLADE_ERROR("Cannot replace position keyframe. Index out of range.");
		}
	}

	void Animation::ClearKeyframes() noexcept
	{
		m_PositionKeyframes.clear();
		m_RotationKeyframes.clear();
		m_ScalingKeyframes.clear();
	}

	void Animation::SortPositionKeyframes() noexcept
	{
		std::sort(m_PositionKeyframes.begin(), m_PositionKeyframes.end());
	}

	void Animation::SortRotationKeyframes() noexcept
	{
		std::sort(m_RotationKeyframes.begin(), m_RotationKeyframes.end());
	}

	void Animation::SortScalingKeyframes() noexcept
	{
		std::sort(m_ScalingKeyframes.begin(), m_ScalingKeyframes.end());
	}
}
