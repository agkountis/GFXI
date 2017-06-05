#ifndef LIBNCF_UTIL_H_INCLUDED
#define LIBNCF_UTIL_H_INCLUDED

#include <string>
#include "declspec.h"

#ifdef _WIN32
#define CONFIG_DELIM_PATH '\\'
#else
#define CONFIG_DELIM_PATH '/'
#endif /* _WIN32 */

namespace Util {
	namespace String {

NCF_DECLSPEC void   to_lower_case(std::string &s);           // Convert to lower case.
NCF_DECLSPEC void   to_upper_case(std::string &s);           // Convert to upper case.
NCF_DECLSPEC bool   to_bool(const std::string &s);           // Convert to boolean type.
NCF_DECLSPEC int	to_int(const std::string &s);            // Convert to integer type.
NCF_DECLSPEC float  to_float(const std::string &s);          // Convert to float type.
NCF_DECLSPEC double to_double(const std::string &s);         // Convert to double type.
NCF_DECLSPEC void   to_string(std::string &out, bool val);   // Convert to string.
NCF_DECLSPEC void   to_string(std::string &out, int val);    // Convert to string.
NCF_DECLSPEC void   to_string(std::string &out, float val);  // Convert to string.
NCF_DECLSPEC void   to_string(std::string &out, double val); // Convert to string.

NCF_DECLSPEC void strip(std::string &s, char c); // Removes all occurrences of the given character.
NCF_DECLSPEC void unquote(std::string &s);       // Trims '"' at start and end.
NCF_DECLSPEC void trim_left(std::string &s);     // Trims ' ', '\t' at the start of the given string.
NCF_DECLSPEC void trim_right(std::string &s);    // Trims ' ', '\n', '\t', '\r' at the end.
NCF_DECLSPEC void trim(std::string &s);          // Trims ' ', '\n', '\t', '\r' at the start and end.

// Splits the given array into two string at first occurance of given char.
NCF_DECLSPEC void split(std::string in, std::string &left, std::string &right, char c);
// Extracts the first balanced substring included between two pX chars.
NCF_DECLSPEC void extract(std::string &s, std::string &t, const char p1, const char p2);
// Extracts the base name and path from a string.
NCF_DECLSPEC void path_comp(const std::string &s, std::string &base, std::string &file, const char delim = CONFIG_DELIM_PATH);
// Replace a matched substring p with r.
NCF_DECLSPEC void replace_first_of(std::string &s, const std::string &p, const std::string &r);

	} /* namespace String */
} /* namespace Util */

#endif /* LIBNCF_UTIL_H_INCLUDED */
