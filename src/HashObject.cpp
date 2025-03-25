/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "HashObject.hpp"
#include "StrUtil.hpp"

using namespace std;


Logger HashObject::logger = Logger::getLogger("HashObject");

int32_t HashObject::getInt(string key) {
	return StrUtil::toInt(get(key));
}

uint32_t HashObject::getUInt(string key) {
	return StrUtil::toUInt(get(key));
}

int64_t HashObject::getLong(string key) {
	return StrUtil::toLong(get(key));
}

uint64_t HashObject::getULong(string key) {
	return StrUtil::toULong(get(key));
}

float HashObject::getFloat(string key) {
	return StrUtil::toFloat(get(key));
}

double HashObject::getDouble(string key) {
	return StrUtil::toDouble(get(key));
}
