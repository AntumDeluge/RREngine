/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_LOADER_H
#define RRE_FONT_MAP_LOADER_H

#include <unordered_map>

#include <tinyxml2.h>


namespace FontMapLoader {

	/**
	 * Loads configured font maps from configuration in `data/conf/fonts.xml`.
	 */
	void loadConfig();

	/**
	 * Creates a font map from XML data.
	 *
	 * FIXME: make private; not needed by other namespaces/classes
	 *
	 * @param el
	 *   Element containing font information.
	 * @return
	 *   `true` if parsing succeeded.
	 */
	bool parseFont(tinyxml2::XMLElement* el);

	/**
	 * Parses mapping of character index.
	 *
	 * FIXME: make private; not needed by other namespaces/classes
	 *
	 * @param el
	 *   Element containing starting index & associated characters.
	 * @return
	 *   Mapping of indexed characters.
	 */
	std::unordered_map<wchar_t, int> parseCharacters(tinyxml2::XMLElement* el);
};

#endif /* RRE_FONT_MAP_LOADER_H */
