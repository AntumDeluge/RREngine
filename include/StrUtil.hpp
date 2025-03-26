/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_STR_UTIL
#define RRE_STR_UTIL

#include <cstdint> // *int*_t
#include <sstream>
#include <string>
#include <type_traits> // std::is_same
#include <utility> // std::pair


/**
 * Return type for string parsing functions.
 */
typedef std::pair<int32_t, std::string> ParseResult;

/**
 * String related functions.
 */
namespace StrUtil {

	/**
	 * Converts value to string.
	 *
	 * Define in header so required instances are created dynamically.
	 *
	 * FIXME: wide character strings not supported
	 *
	 * @param v
	 *   Value to be converted (`std::string`, `char`, or `char*`).
	 * @return
	 *   `std::string` equivalent.
	 */
	template <typename T>
	std::string check(const T& v) {
		static_assert(
			std::is_same<T, std::string>::value
			|| std::is_same<T, char>::value
			|| std::is_same<T, char*>::value
			|| std::is_same<T, const char*>::value,
			"Argument must be of type std::string, char, or char*");

		std::stringstream ss;
		ss << v;
		return ss.str();
	}

	/**
	 * Trims leading & traling whitespace from a string.
	 *
	 * @param st
	 *   Value to be trimmed.
	 * @return
	 *   Trimmed string.
	 */
	std::string trim(std::string st);

	/**
	 * Converts all characters to lowercase.
	 *
	 * @param st
	 *   String to be converted.
	 * @return
	 *   Lowercase string.
	 */
	std::string toLower(std::string st);

	/**
	 * Converts all characters to uppercase.
	 *
	 * @param st
	 *   String to be converted.
	 * @return
	 *   Uppercase string.
	 */
	std::string toUpper(std::string st);

	/**
	 * Parses short value from a string.
	 *
	 * @param s
	 * @param st
	 *   String to be parsed.
	 * @return
	 *   Parse result with error message.
	 */
	ParseResult parseShort(int16_t& s, std::string st);

	/**
	 * Parses unsigned short value from a string.
	 *
	 * @param s
	 * @param st
	 *   String to be parsed.
	 * @return
	 *   Parse result with error message.
	 */
	ParseResult parseUShort(uint16_t& s, std::string st);

	/**
	 * Parses integer value from a string.
	 *
	 * @param i
	 * @param st
	 *   String to be parsed.
	 * @return
	 *   Parse result with error message.
	 */
	ParseResult parseInt(int32_t& i, std::string st);

	/**
	 * Parses unsigned integer value from a string.
	 *
	 * @param i
	 * @param st
	 *   String to be parsed.
	 * @return
	 *   Parse result with error message.
	 */
	ParseResult parseUInt(uint32_t& i, std::string st);

	/**
	 * Parses long value from a string.
	 *
	 * @param l
	 * @param st
	 *   String to be parsed.
	 * @return
	 *   Parse result with error message.
	 */
	ParseResult parseLong(int64_t& l, std::string st);

	/**
	 * Parses unsigned long value from a string.
	 *
	 * @param l
	 * @param st
	 *   String to be parsed.
	 * @return
	 *   Parse result with error message.
	 */
	ParseResult parseULong(uint64_t& l, std::string st);

	/**
	 * Parses float value from a string.
	 *
	 * @param f
	 * @param st
	 *   String to be parsed.
	 * @return
	 *   Parse result with error message.
	 */
	ParseResult parseFloat(float& f, std::string st);

	/**
	 * Parses double value from a string.
	 *
	 * @param d
	 * @param st
	 *   String to be parsed.
	 * @return
	 *   Parse result with error message.
	 */
	ParseResult parseDouble(double& d, std::string st);

	/**
	 * Parses boolean value from a string.
	 *
	 * @param b
	 * @param st
	 *   String to be parsed.
	 * @return
	 *   Parse result with error message.
	 */
	ParseResult parseBool(bool& b, std::string st);
}

#endif /* RRE_STR_UTIL */
