#ifndef BLADE_LIGHT_COMPONENT_H_
#define BLADE_LIGHT_COMPONENT_H_
#include "component.h"

namespace Blade
{
	enum class LightType
	{
		POSITIONAL,
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

	struct SpotLightDesc : PointLightDesc, DirectionalLightDesc
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

		void Setup() noexcept override;

		void Update(float dt, long time) noexcept override;

		void Teardown() noexcept override;
	};

	class PointLightComponent : public LightComponent
	{
	private:
		PointLightDesc m_LightDescription;

	public:
		PointLightComponent(const PointLightDesc& lightDesc,
		                    LightType lightType,
		                    Entity* parent) : LightComponent{ lightType, parent },
		                                      m_LightDescription{ lightDesc }
		{
		}

		const PointLightDesc& GetLightDescription() const noexcept;

		PointLightDesc* GetLightDescriptionPtr() const noexcept;

		void Setup() noexcept override;

		void Update(float dt, long time) noexcept override;

		void Teardown() noexcept override;
	};

	class DirectionalLightComponent : public LightComponent
	{
	private:
		DirectionalLightDesc m_LightDescription;

	public:
		DirectionalLightComponent(const DirectionalLightDesc& lightDesc,
		                          LightType lightType,
		                          Entity* parent) : LightComponent{ lightType, parent },
		                                            m_LightDescription{ lightDesc }
		{
		}

		const DirectionalLightDesc& GetLightDescription() const noexcept;

		DirectionalLightDesc* GetLightDescriptionPtr() const noexcept;
	};

	class SpotLightComponent : public LightComponent
	{
	private:
		SpotLightDesc m_LightDescription;

	public:
		SpotLightComponent(const SpotLightDesc& lightDesc,
		                   LightType lightType,
		                   Entity* parent) : LightComponent{ lightType, parent },
		                                     m_LightDescription{ lightDesc }
		{
		}

		const SpotLightDesc& GetLightDescription() const noexcept;

		SpotLightDesc* GetLightDescriptionPtr() const noexcept;
	};
}

#endif //BLADE_LIGHT_COMPONENT_H_
