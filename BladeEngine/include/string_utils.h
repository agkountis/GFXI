#ifndef BLADE_STRING_UTILS_H_
#define BLADE_STRING_UTILS_H_
#include <string>

namespace Blade
{
	namespace StringUtils
	{
		std::string ToString(const std::wstring& wstring);

		std::wstring ToWstring(const std::string& string);
	}
}

#endif //BLADE_STRING_UTILS_H_
