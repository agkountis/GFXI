#include "string_utils.h"
#include <locale>
#include <codecvt>

namespace Blade
{
	namespace StringUtils
	{
		std::string ToString(const std::wstring& wstring)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

			return converter.to_bytes(wstring);
		}

		std::wstring ToWstring(const std::string& string)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

			return converter.from_bytes(string);
		}
	}
}
