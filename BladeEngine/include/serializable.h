#ifndef BLADE_SERIALIZABLE_H_
#define BLADE_SERIALIZABLE_H_
#include <vector>
#include "types.h"

namespace Blade
{
	/**
	\brief Serializable Interface of the engine
	*/
	class Serializable
	{
	public:
		virtual ~Serializable() = default;

		/**
		\brief Serialize the object
		\return The serialized object represented by a vector of bytes.
		*/
		virtual std::vector<Byte> Serialize() noexcept = 0;
	};
}

#endif //BLADE_SERIALIZABLE_H_
