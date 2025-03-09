/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_LOADER_H
#define RRE_FONT_MAP_LOADER_H

#include <cstddef> // size_t
#include <cstdint> // uint*_t
#include <unordered_map>

#include <tinyxml2.h>


// TODO: rename to FontMapsLoader
namespace FontMapLoader {

	/**
	 * Loads configured font maps from built-in data.
	 */
	bool loadBuiltin();

	/**
	 * Loads configured font maps from configuration in `data/conf/fonts.xml`.
	 */
	bool loadConfig();

	/**
	 * Creates a font map from XML data.
	 *
	 * FIXME: make private; not needed by other namespaces/classes
	 *
	 * @param el
	 *   Element containing font information.
	 * @param data
	 *   PNG image data to use for map texture. if `NULL`, uses path parsed from XML.
	 * @param data_size
	 *   Data's byte count to be read.
	 * @return
	 *   `true` if parsing succeeded.
	 */
	bool parseFont(tinyxml2::XMLElement* el, const uint8_t data[], const size_t data_size);

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
