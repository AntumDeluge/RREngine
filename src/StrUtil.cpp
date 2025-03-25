/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <cctype> // std::tolower, std::toupper
#include <sstream>
#include <type_traits>

#include "Logger.hpp"
#include "StrUtil.hpp"

using namespace std;


static Logger logger = Logger::getLogger("StrUtil");

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

string StrUtil::trim(string st) {
	std::size_t f = st.find_first_not_of(" \t\n\r\f\v");
	if (f == string::npos) {
		// string only contains whitespace
		return "";
	}
	std::size_t l = st.find_last_not_of(" \t\n\r\f\v");
	return st.substr(f, l - f + 1); // @suppress("Invalid arguments")
}

string StrUtil::toLower(string st) {
	string l_value = "";
	for (uint32_t idx = 0; idx < st.length(); idx++) {
		l_value += tolower(st[idx]);
	}
	return l_value;
}

string StrUtil::toUpper(string st) {
	string u_value = "";
	for (uint32_t idx = 0; idx < st.length(); idx++) {
		u_value += toupper(st[idx]);
	}
	return u_value;
}

int32_t StrUtil::toInt(string st) {
	string err;
	try {
		return stoi(st);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert string value \"" + st + "\" to int: " + err);
	return 0;
}

uint32_t StrUtil::toUInt(string st) {
	string err;
	try {
		return static_cast<uint32_t>(stoul(st));
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert string value \"" + st + "\" to unsigned int: " + err);
	return 0;
}

int64_t StrUtil::toLong(string st) {
	string err;
	try {
		return stoll(st);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert string value \"" + st + "\" to long: " + err);
	return 0;
}

uint64_t StrUtil::toULong(string st) {
	string err;
	try {
		return stoull(st);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert string value \"" + st + "\" to unsigned long: " + err);
	return 0;
}

float StrUtil::toFloat(string st) {
	string err;
	try {
		return stof(st);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert string value \"" + st + "\" to float: " + err);
	return 0;
}

double StrUtil::toDouble(string st) {
	string err;
	try {
		return stod(st);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert string value \"" + st + "\" to double: " + err);
	return 0;
}
