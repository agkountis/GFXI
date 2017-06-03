#ifndef BLADE_LIGHT_COMPONENT_H_
#define BLADE_LIGHT_COMPONENT_H_
#include "component.h"

namespace Blade
{
	/**
	 * \brief An enumeration used to specify a light type.
	 */
	enum class LightType
	{
		POINT,
		DIRECTIONAL,
		SPOTLIGHT
	};

	/**
	 * \brief A struct describing a point light.
	 * \details This struct is also used to represent a point light in shaders.
	 */
	struct PointLightDesc
	{
		Vec4f ambientIntensity;
		Vec4f diffuseIntensity;
		Vec4f specularIntensity;
		Vec3f position;
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
		Vec2f pad;
	};

	/**
	 * \brief A struct describing a directional light.
	 * \details This struct is also used to represent a directional light in shaders.
	 */
	struct DirectionalLightDesc
	{
		Vec4f ambientIntensity;
		Vec4f diffuseIntensity;
		Vec4f specularIntensity;
		Vec3f direction;
		float pad;
	};

	/**
	 * \brief A struct describing a spotlight
	 * \details This struct is also used to represent a spotlight in shaders.
	 */
	struct SpotlightDesc
	{
		Vec4f ambientIntensity;
		Vec4f diffuseIntensity;
		Vec4f specularIntensity;
		Vec3f position;
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
		Vec3f direction;
		float spotCutoff;
		float spotExponent;
		float pad;
	};

	/**
	 * \brief Abstract class that describes a LightComponent. Provides
	 * the base functinality of a LightComponent. It contains the component's
	 * type and an index to the entry of the correct light description cache in the LightSystem.
	 * Managed by the LightSystem.
	 */
	class LightComponent : public Component
	{
	private:
		/**
		 * \brief Specifies the type of the LightComponent.
		 * Used primarily by the LightSystem to manage it's light description caches.
		 */
		LightType m_LightType;

		/**
		 * \brief An index to the entry of the light description cache contained in the light system.
		 * \details Used primarily by the Light system during component uregistration.
		 */
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

	};
}

#endif //BLADE_LIGHT_COMPONENT_H_
