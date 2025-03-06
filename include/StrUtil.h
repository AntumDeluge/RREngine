/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_STR_UTIL
#define RRE_STR_UTIL

#include <string>


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
}

#endif /* RRE_STR_UTIL */
