/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <sstream>
#include <type_traits>

using namespace std;

#include "StrUtil.h"


template <typename T>
string StrUtil::check(const T& v) {
	static_assert(
		is_same<T, string>::value
		|| is_same<T, char>::value
		|| is_same<T, char*>::value
		|| is_same<T, const char*>::value,
		"Argument must be of type std::string, char, or char*");

	stringstream ss;
	ss << v;
	return ss.str();
}
