/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <cctype> // std::tolower, std::toupper

#include "Logger.hpp"
#include "StrUtil.hpp"

using namespace std;


static Logger logger = Logger::getLogger("StrUtil");

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

ParseResult StrUtil::parseShort(int16_t& s, string st) {
	ParseResult res;
	try {
		s = static_cast<int16_t>(stoi(st));
		res.first = 0;
	} catch (const exception& e) {
		res.first = 1;
		res.second = e.what();
	}
	return res;
}

ParseResult StrUtil::parseUShort(uint16_t& s, string st) {
	ParseResult res;
	try {
		s = static_cast<uint16_t>(stoul(st));
		res.first = 0;
	} catch (const exception& e) {
		res.first = 1;
		res.second = e.what();
	}
	return res;
}

ParseResult StrUtil::parseInt(int32_t& i, string st) {
	ParseResult res;
	try {
		i = stoi(st);
		res.first = 0;
	} catch (const exception& e) {
		res.first = 1;
		res.second = e.what();
	}
	return res;
}

ParseResult StrUtil::parseUInt(uint32_t& i, string st) {
	ParseResult res;
	try {
		i = static_cast<uint32_t>(stoul(st));
		res.first = 0;
	} catch (const exception& e) {
		res.first = 1;
		res.second = e.what();
	}
	return res;
}

ParseResult StrUtil::parseLong(int64_t& l, string st) {
	ParseResult res;
	try {
		l = stoll(st);
		res.first = 0;
	} catch (const exception& e) {
		res.first = 1;
		res.second = e.what();
	}
	return res;
}

ParseResult StrUtil::parseULong(uint64_t& l, string st) {
	ParseResult res;
	try {
		l = stoull(st);
		res.first = 0;
	} catch (const exception& e) {
		res.first = 1;
		res.second = e.what();
	}
	return res;
}

ParseResult StrUtil::parseFloat(float& f, string st) {
	ParseResult res;
	try {
		f = stof(st);
		res.first = 0;
	} catch (const exception& e) {
		res.first = 1;
		res.second = e.what();
	}
	return res;
}

ParseResult StrUtil::parseDouble(double& d, string st) {
	ParseResult res;
	try {
		d = stod(st);
		res.first = 0;
	} catch (const exception& e) {
		res.first = 1;
		res.second = e.what();
	}
	return res;
}

ParseResult StrUtil::parseBool(bool& b, string st) {
	ParseResult res;
	string temp = StrUtil::toLower(StrUtil::trim(st));
	bool t = temp.compare("true") == 0;
	if (t || temp.compare("false") == 0) {
		b = t;
		res.first = 0;
	} else {
		res.first = 1;
		res.second = "Unrecognized string: \"" + st + "\"";
	}
	return res;
}
