#ifndef BLADE_RENDER_SYSTEM_H_
#define BLADE_RENDER_SYSTEM_H_
#include "system.h"
#include <vector>
#include "pipeline.h"

namespace Blade
{
	/**
	 * \brief A System responsible for processing the RenderComponents by
	 * passing them through a specified pipeline.
	 */
	class RenderSystem : public System
	{
	private:
		/**
		 * \brief A pipeline of that processes RenderComponents.
		 */
		RenderPassPipeline* m_RenderPassPipeline{ nullptr };
		
		/**
		 * \brief The registered RenderComponents to be processed.
		 * by the RenderSystem.
		 */
		std::vector<RenderComponent*> m_RenderComponents;

		bool m_Sort{ false };
		
	public:
		/**
		 * \brief Destructor of the RenderSystem. Deallocates the pipeline member.
		 */
		~RenderSystem();

		/**
		 * \brief Registeres a RenderComponent to the RenderSystem.
		 * \param renderComponent The component to be registered to the RenderSytstem for processing.
		 */
		void RegisterComponent(RenderComponent* renderComponent) noexcept;

		/**
		 * \brief Unregisters a RenderComponent from the RenderSystem.
		 * \param id The unique id of the RenderComponent to be unregistered.
		 */
		void UnregisterComponent(int id) noexcept;

		/**
		 * \brief Sets the pipeline that the RenderSystem will pass the RenderComponents through.
		 * \param renderPassPipeline The pipeline that processes the RenderComponents.
		 */
		void SetRenderPassPipeline(RenderPassPipeline* renderPassPipeline) noexcept;

		/**
		 * \brief Removed the pipeline from the RenderSystem if one is set.
		 */
		void ClearRenderPassPipeline() noexcept;

		/**
		 * \brief Initializes the RenderSystem.
		 * \return TRUE if initialization is successfull, FALSE otherwise.
		 */
		bool Initialize() noexcept override;
		
		/**
		 * \brief Processes the RenderComponents by passing them through the RenderPassPipeline.
		 * \param deltaTime The time elapsed from the previous frame of the application.
		 */
		void Process(float deltaTime=.0f, long time=0) noexcept override;

		/**
		\brief Set the sorting flag
		\details If sorting is enable, the render components are sorted by alpha value.
		\param sorting The sorting flag: TRUE enable sorting.
		*/
		void SetSorting(bool sorting) noexcept;
	};
}

#endif //BLADE_RENDER_SYSTEM_H_
