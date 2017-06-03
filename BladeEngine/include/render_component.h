#ifndef BLADE_RENDER_COMPONENT_H_
#define BLADE_RENDER_COMPONENT_H_
#include "component.h"
#include "mesh.h"
#include "material.h"

namespace Blade
{
	/**
	 * \brief Represents a RenderComponent. The RenderComponent
	 * makes an entity renderable. This component is processed by the
	 * RenderSystem.
	 */
	class RenderComponent : public Component
	{
	private:
		/**
		 * \brief A pointer the the geometry.
		 */
		Mesh* m_Mesh{ nullptr };

		/**
		 * \brief The material to be used for the rendering.
		 */
		Material m_Material;

	public:
		/**
		 * \brief RenderComponent's constructor. Registers the RenderComponent
		 * to the RenderSystem.
		 * \param parent The entity the component will be attached to.
		 */
		explicit RenderComponent(Entity* parent);

		/**
		 * \brief RenderComponent's destructor. Unregisters the RenderComponent
		 * from the RenderSystem.
		 */
		~RenderComponent();

		/**
		 * \brief Provides a pointer to the Mesh contained in the RenderComponent.
		 * \return The pointer to the Mesh of the RenderComponent.
		 */
		Mesh* GetMesh() const noexcept;

		/**
		 * \brief Sets the specified Mesh to the RenderComponent.
		 * \param mesh The mesh to be used when rendering.
		 */
		void SetMesh(Mesh* mesh) noexcept;

		/**
		 * \brief Provides the Material of the RenderComponent.
		 * \return The Material of the RenderComponent.
		 */
		const Material& GetMaterial() const noexcept;

		/**
		 * \brief Sets the specified Material to the RenderComponent.
		 * \param material The Material to be set.
		 */
		void SetMaterial(const Material& material) noexcept;
	};
}

#endif //BLADE_RENDER_COMPONENT_H_
