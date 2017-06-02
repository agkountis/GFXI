#ifndef BLADE_SERIALIZATION_UTILS_H_
#define BLADE_SERIALIZATION_UTILS_H_
#include <vector>
#include "types.h"

namespace Blade
{
	namespace SerializationUtils
	{
		template<typename T>
		void Pack(std::vector<Byte>& destination, T& data)
		{
			Byte* src{ reinterpret_cast<Byte*>(&data) };
			destination.insert(destination.end(), src, src + sizeof(T));
		}

		template <typename T>
		void Unpack(std::vector<Byte>& source, int index, T& data) {
			Byte* buffer{ source.data() };

			buffer += index;

			data = *reinterpret_cast<T*>(buffer);
		}
	}
}

#endif //BLADE_SERIALIZATION_UTILS_H_
