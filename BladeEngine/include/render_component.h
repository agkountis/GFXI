#ifndef BLADE_RENDER_COMPONENT_H_
#define BLADE_RENDER_COMPONENT_H_
#include "component.h"
#include "mesh.h"
#include "material.h"

namespace Blade
{
	class RenderComponent : public Component
	{
	private:
		Mesh* m_Mesh{ nullptr };

		Material m_Material;

	public:
		explicit RenderComponent(Entity* parent);

		~RenderComponent();

		Mesh* GetMesh() const noexcept;

		void SetMesh(Mesh* mesh) noexcept;

		const Material& GetMaterial() const noexcept;

		void SetMaterial(const Material& material) noexcept;

		void Setup() noexcept override;

		void Update(float dt, long time = 0) noexcept override;

		void Teardown() noexcept override;
	};
}

#endif //BLADE_RENDER_COMPONENT_H_
