#ifndef BLADE_SERIALIZABLE_H_
#define BLADE_SERIALIZABLE_H_
#include <vector>
#include "types.h"

namespace Blade
{
	class Serializable
	{
	public:
		virtual ~Serializable() = default;

		virtual std::vector<Byte> Serialize() noexcept = 0;
	};
}

#endif //BLADE_SERIALIZABLE_H_
