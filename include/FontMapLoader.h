/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_LOADER_H
#define RRE_FONT_MAP_LOADER_H

#include <unordered_map>

#include <tinyxml2.h>

#include "Logger.h"


class FontMapLoader {
private:
	// singleton class
	static FontMapLoader* instance;
	FontMapLoader() {
		this->logger = Logger::getLogger("FontMapLoader");
		this->loaded = false;
	}
	~FontMapLoader();

	// delete copy constructor & assignment operator
	FontMapLoader(const FontMapLoader&) = delete;
	FontMapLoader& operator=(const FontMapLoader&) = delete;

	Logger* logger;
	bool loaded;

public:
	static FontMapLoader* get() {
		if (FontMapLoader::instance == nullptr) {
			FontMapLoader::instance = new FontMapLoader();
		}
		return FontMapLoader::instance;
	}

	/**
	 * Loads configured font maps from configuration in `data/conf/fonts.xml`.
	 */
	void loadConfig();

	bool parseFont(tinyxml2::XMLElement* el);

	std::unordered_map<wchar_t, unsigned int> parseCharacters(tinyxml2::XMLElement* el);
};

#endif /* RRE_FONT_MAP_LOADER_H */
