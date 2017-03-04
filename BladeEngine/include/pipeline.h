#ifndef BLADE_PIPELINE_H_
#define BLADE_PIPELINE_H_
#include <vector>
#include "pipeline_stage.h"
#include "render_component.h"
#include "d3d/D3D11_render_target.h"

namespace Blade
{
	/**
	 * \brief Abstract class that describes a pipeline that processes the specified object data type.
	 * \tparam T The type of data that the Pipeline's PipelineStages will process.
	 * \tparam Tdata The type of data that the PipelineStages will return after executed.
	 */
	template<typename T, typename Tdata>
	class Pipeline
	{
	private:
		/**
		 * \brief The PipelineStages to be excuted.
		 */
		std::vector<PipelineStage<T, Tdata>*> m_Stages;

	public:
		/**
		 * \brief Adds a PipelineStage to the Pipeline.
		 * \param stage The PipelineStage to be added to the Pipeline.
		 */
		void AddStage(PipelineStage<T, Tdata>* stage)
		{
			m_Stages.push_back(stage);
		}

		/**
		 * \brief Processes the objects provided by passing then through each PipelineStage.
		 * \param data The objects to be processed by the Pipeline's stages.
		 */
		void Execute(const std::vector<T>& data)
		{
			PipelineData<Tdata> prevStageData{ nullptr };
			for (auto stage : m_Stages)
			{
				prevStageData = stage->Execute(data, prevStageData);

			}
		}
	};

#if defined(BLADE_BUILD_D3D)
	/**
	 * \brief Type alias for a RenderPass Pipeline.
	 */
	using RenderPassPipeline = Pipeline<RenderComponent*, D3D11RenderTarget*>;
#else
#endif
}

#endif //BLADE_PIPELINE_H_
