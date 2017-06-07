#ifndef BLADE_RESOURCE_H_
#define BLADE_RESOURCE_H_
#include <string>

namespace Blade
{
	/*
	\brief Resource class of the engine
	\details A resource is type agnostic.
	*/
	class Resource
	{
	private:
		/*
		\brief ID of the resource
		*/
		unsigned int m_Id;

	public:
		Resource() : m_Id{ 0 }
		{
		}

		explicit Resource(unsigned int id) : m_Id{ id }
		{
		}

		virtual ~Resource();

		/*
		\brief Getter of the resource id
		\return Resource ID
		*/
		unsigned int GetId() const noexcept
		{
			return m_Id;
		}

		/*
		\brief Setter for the resource ID
		\param id the resource ID
		*/
		void SetId(unsigned int id) noexcept
		{
			m_Id = id;
		}

		/*
		\brief Load a resource form a file
		\param file_name The path of the file where the resource is stored.
		*/
		virtual bool Load(const std::wstring& file_name) noexcept = 0;
	};
}

#endif //BLADE_RESOURCE_H_
