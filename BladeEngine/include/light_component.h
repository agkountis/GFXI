#ifndef BLADE_LIGHT_COMPONENT_H_
#define BLADE_LIGHT_COMPONENT_H_
#include "component.h"

namespace Blade
{
	enum class LightType
	{
		POINT,
		DIRECTIONAL,
		SPOTLIGHT
	};

	struct LightDesc
	{
		Vec4f ambientIntensity;
		Vec4f diffuseIntensity;
		Vec4f specularIntensity;
		bool active;
	};

	struct PointLightDesc : LightDesc
	{
		Vec3f position;
	};

	struct DirectionalLightDesc : LightDesc
	{
		Vec3f direction;
	};

	struct SpotlightDesc : PointLightDesc, DirectionalLightDesc
	{
		float spotCutoff;
		float spotExponent;
	};

	class LightComponent : public Component
	{
	private:
		LightType m_LightType;

		int m_LightDescCacheIndex{ -1 };

	public:
		LightComponent(LightType lightType, Entity* parent)
			: Component{ "co_light", parent },
			  m_LightType{ lightType }
		{
		}

		LightType GetLightType() const noexcept
		{
			return m_LightType;
		}

		int GetLightDescCacheIndex() const noexcept
		{
			return m_LightDescCacheIndex;
		}

		void SetLightDescCacheIndex(int index) noexcept
		{
			m_LightDescCacheIndex = index;
		}

		void Setup() noexcept override = 0;

		void Update(float dt, long time) noexcept override = 0;

		void Teardown() noexcept override = 0;
	};
}

#endif //BLADE_LIGHT_COMPONENT_H_
