/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_HASH_OBJECT
#define RRE_HASH_OBJECT

#include <cstdint> // *int*_t
#include <sstream>
#include <string>
#include <unordered_map>

#include "Logger.hpp"


/**
 * Object with hashable properties.
 */
class HashObject {
private:
	static Logger logger;

	/** Hashed data. */
	std::unordered_map<std::string, std::string> data;

public:
	/** Default constructor. */
	HashObject() {}

	/**
	 * Copy constructor.
	 *
	 * @param other
	 *   Object to be copied.
	 */
	HashObject(const HashObject& other) {
		for (auto p: other.data) {
			set(p.first, p.second);
		}
	}

	/** Virtual default destructor. */
	virtual ~HashObject() = default;

	/**
	 * Overload index operator to allow access to properties data.
	 *
	 * @param key
	 *   Property key.
	 */
	std::string& operator[](std::string key) {
		return data[key];
	}

	/** Iterable begin method. */
	auto begin() {
		return data.begin();
	}

	/** Iterable end method. */
	auto end() {
		return data.end();
	}

	/**
	 * Sets a property.
	 *
	 * @param key
	 *   Property key.
	 * @param value
	 *   Property value.
	 */
	template <typename T>
	void set(std::string key, T value) {
		std::stringstream ss;
		ss << value;
		data[key] = ss.str();
	}

	/**
	 * Removes a property.
	 *
	 * @param key
	 *   Property key to remove.
	 */
	void unset(std::string key) {
		data.erase(key);
	}

	/**
	 * Checks if object has a property.
	 *
	 * @param key
	 *   Propety key.
	 * @return
	 *   `true` if `key` index is found in properties table.
	 */
	bool has(std::string key) const {
		return data.find(key) != data.end();
	}

	/**
	 * Retrieves a property value.
	 *
	 * @param key
	 *   Property key.
	 * @return
	 *   String value or empty string if property not set.
	 */
	std::string get(std::string key) const {
		// use an iterator so data not modified using [] operator
		auto iter = data.find(key);
		if (iter != data.end()) {
			return iter->second;
		}
		return "";
	}

	/**
	 * Retreivies a property integer value.
	 *
	 * @param key
	 *   Property key.
	 * @return
	 *   Integer value or 0 if property not set.
	 */
	int32_t getInt(std::string key) const;

	/**
	 * Retreivies a property unsigned integer value.
	 *
	 * @param key
	 *   Property key.
	 * @return
	 *   Unsigned integer value or 0 if property not set.
	 */
	uint32_t getUInt(std::string key) const;

	/**
	 * Retreivies a property long value.
	 *
	 * @param key
	 *   Property key.
	 * @return
	 *   Long value or 0 if property not set.
	 */
	int64_t getLong(std::string key) const;

	/**
	 * Retreivies a property unsigned long value.
	 *
	 * @param key
	 *   Property key.
	 * @return
	 *   Unsigned long value or 0 if property not set.
	 */
	uint64_t getULong(std::string key) const;

	/**
	 * Retreivies a property float value.
	 *
	 * @param key
	 *   Property key.
	 * @param def
	 *   Default value to return if property not set.
	 * @return
	 *   Float value or 0 if property not set.
	 */
	float getFloat(std::string key, float def=0.0f) const;

	/**
	 * Retreivies a property double value.
	 *
	 * @param key
	 *   Property key.
	 * @return
	 *   Double value or 0 if property not set.
	 */
	double getDouble(std::string key) const;
};

#endif /* RRE_HASH_OBJECT */
