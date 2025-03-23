/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "HashObject.hpp"

using namespace std;


Logger HashObject::logger = Logger::getLogger("HashObject");

int32_t HashObject::getInt(string key) {
	string s_value = get(key);
	string err;
	try {
		return stoi(s_value);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert key \"" + key + "\" value \"" + s_value + "\" to int: " + err);
	return 0;
}

uint32_t HashObject::getUInt(string key) {
	string s_value = get(key);
	string err;
	try {
		return static_cast<uint32_t>(stoul(s_value));
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert key \"" + key + "\" value \"" + s_value + "\" to unsigned int: "
			+ err);
	return 0;
}

int64_t HashObject::getLong(string key) {
	string s_value = get(key);
	string err;
	try {
		return stoll(s_value);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert key \"" + key + "\" value \"" + s_value + "\" to long: " + err);
	return 0;
}

uint64_t HashObject::getULong(string key) {
	string s_value = get(key);
	string err;
	try {
		return stoull(s_value);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert key \"" + key + "\" value \"" + s_value + "\" to unsigned long: "
			+ err);
	return 0;
}

float HashObject::getFloat(string key) {
	string s_value = get(key);
	string err;
	try {
		return stof(s_value);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert key \"" + key + "\" value \"" + s_value + "\" to float: " + err);
	return 0;
}

double HashObject::getDouble(string key) {
	string s_value = get(key);
	string err;
	try {
		return stod(s_value);
	} catch (const exception& e) {
		err = e.what();
	}
	logger.error("Cannot convert key \"" + key + "\" value \"" + s_value + "\" to double: " + err);
	return 0;
}
