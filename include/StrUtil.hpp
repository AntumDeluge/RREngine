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


/**
 * String related functions.
 */
namespace StrUtil {

	/**
	 * Error for parsing string values.
	 *
	 * TODO: return `ParseError` from converstion/parsing functions
	 */
	//typedef std::pair<uint32_t, std::string> ParseError;

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
	 * Converts string to integer.
	 *
	 * @param st
	 *   String to convert.
	 * @return
	 *   Integer value or 0 if conversion fails.
	 */
	int32_t toInt(std::string st);

	/**
	 * Converts string to unsigned integer.
	 *
	 * FIXME: should take a reference parameter & return error code
	 *
	 * @param st
	 *   String to convert.
	 * @return
	 *   Unsigned integer value or 0 if conversion fails.
	 */
	uint32_t toUInt(std::string st);

	/**
	 * Converts string to long.
	 *
	 * @param st
	 *   String to convert.
	 * @return
	 *   Long value or 0 if conversion fails.
	 */
	int64_t toLong(std::string st);

	/**
	 * Converts string to unsigned long.
	 *
	 * @param st
	 *   String to convert.
	 * @return
	 *   Unsigned long value or 0 if conversion fails.
	 */
	uint64_t toULong(std::string st);

	/**
	 * Converts string to float.
	 *
	 * @param st
	 *   String to convert.
	 * @return
	 *   Float value or 0 if conversion fails.
	 */
	float toFloat(std::string st);

	/**
	 * Converts string to double.
	 *
	 * @param st
	 *   String to convert.
	 * @return
	 *   Double value or 0 if conversion fails.
	 */
	double toDouble(std::string st);

	/**
	 * Converts string to boolean.
	 *
	 * @param st
	 *   String to convert.
	 * @return
	 *   `true` if contents of string are "true" case insensitive.
	 */
	bool toBool(std::string st);
}

#endif /* RRE_STR_UTIL */
