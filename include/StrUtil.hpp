/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_STR_UTIL
#define RRE_STR_UTIL

#include <cstdint> // *int*_t
#include <string>


/**
 * String related functions.
 */
namespace StrUtil {

	/**
	 * Converts value to string.
	 *
	 * @param v
	 *   Value to be converted (`std::string`, `char`, or `char*`).
	 * @return
	 *   `std::string` equivalent.
	 */
	template <typename T>
	std::string check(const T& v);

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
}

#endif /* RRE_STR_UTIL */
