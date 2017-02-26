#ifndef BLADE_PIPELINE_STAGE_H_
#define BLADE_PIPELINE_STAGE_H_

namespace Blade
{
	/**
	 * \brief An abstract data container for the data returned by a PipelineStage
	 * \tparam T The type of data the container will hold.
	 */
	template <typename T>
	class PipelineData
	{
	private:
		/**
		 * \brief The data contained in the PipelineData container.
		 */
		T p_Data;

	public:
		/**
		 * \brief PipelineData constructor.
		 * \param data The data to store in the container.
		 */
		explicit PipelineData(T data)
			: p_Data{ data }
		{
		}

		/**
		 * \brief Returns the data contained in the PipelineData container.
		 * \return The data contained in the container.
		 */
		T Get() const noexcept
		{
			return p_Data;
		}
	};

	/**
	 * \brief This class describes an abstract stage of a pipeline that processes the specified type of data
	 * and returns the specified type of data.
	 * \tparam T The type of data the PipelineStage will process.
	 * \tparam Tdata The type of data the PipelineStage will return.
	 */
	template <typename T, typename Tdata>
	class PipelineStage
	{
	private:
		/**
		 * \brief The name of the PipelineStage
		 */
		std::string m_Name;

	public:
		/**
		 * \brief PipelineStage constructor.
		 * \param name The name of the PipelineStage.
		 */
		explicit PipelineStage(const std::string& name)
			: m_Name{ name }
		{
		}

		/**
		 * \brief Default destructor of the PipelineStage.
		 */
		virtual ~PipelineStage() = default;
		
		/**
		 * \brief Initializes the PipelineStage
		 * \return TRUE if initialization succeded, FALSE otherwise.
		 */
		virtual bool Initialize() = 0;

		/**
		 * \brief Processes the vector of objects provided and return the result.
		 * \param data The type of data the PipelineStage will process. 
		 * \param tdata The type of data the PipelineStage will return.
		 * \return A PipelineData container with the the appropriate data type encapsulated.
		 */
		virtual PipelineData<Tdata> Execute(const std::vector<T>& data, const PipelineData<Tdata>& tdata) noexcept = 0;
	};
}

#endif //BLADE_PIPELINE_STAGE_H_
