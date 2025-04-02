/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "HashObject.hpp"
#include "StrUtil.hpp"

using namespace std;


Logger HashObject::logger = Logger::getLogger("HashObject");

int32_t HashObject::getInt(string key) const {
	string s_value = get(key);
	int32_t i_value = 0;
	ParseResult res = StrUtil::parseInt(i_value, s_value);
	if (res.first != 0) {
		logger.error("Cannot parse integer from key \"", key, "\" value \"", s_value, ": ", res.second);
	}
	return i_value;
}

uint32_t HashObject::getUInt(string key) const {
	string s_value = get(key);
	uint32_t i_value = 0;
	ParseResult res = StrUtil::parseUInt(i_value, s_value);
	if (res.first != 0) {
		logger.error("Cannot parse unsigned integer from key \"", key, "\" value \"", s_value, ": ",
				res.second);
	}
	return i_value;
}

int64_t HashObject::getLong(string key) const {
	string s_value = get(key);
	int64_t l_value = 0;
	ParseResult res = StrUtil::parseLong(l_value, s_value);
	if (res.first != 0) {
		logger.error("Cannot parse long from key \"", key, "\" value \"", s_value, ": ", res.second);
	}
	return l_value;
}

uint64_t HashObject::getULong(string key) const {
	string s_value = get(key);
	uint64_t l_value = 0;
	ParseResult res = StrUtil::parseULong(l_value, s_value);
	if (res.first != 0) {
		logger.error("Cannot parse unsigned long from key \"", key, "\" value \"", s_value, ": ",
				res.second);
	}
	return l_value;
}

float HashObject::getFloat(string key) const {
	string s_value = get(key);
	float f_value = 0;
	ParseResult res = StrUtil::parseFloat(f_value, s_value);
	if (res.first != 0) {
		logger.error("Cannot parse float from key \"", key, "\" value \"", s_value, ": ", res.second);
	}
	return f_value;
}

double HashObject::getDouble(string key) const {
	string s_value = get(key);
	double d_value = 0;
	ParseResult res = StrUtil::parseDouble(d_value, s_value);
	if (res.first != 0) {
		logger.error("Cannot parse double from key \"", key, "\" value \"", s_value, ": ", res.second);
	}
	return d_value;
}
