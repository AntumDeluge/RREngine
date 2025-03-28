/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_STORE
#define RRE_FONT_MAP_STORE

#include <string>

#include "FontMap.hpp"
#include "Sprite.hpp"


/**
 * Caches font mappings from configuration.
 */
namespace FontMapStore {

	/**
	 * Caches a font mapping.
	 *
	 * @param font_id
	 *   Font map identifier.
	 * @param font_map
	 *   Font map instance.
	 */
	void add(std::string font_id, FontMap* font_map);

	/**
	 * Retrieves a cached font mapping.
	 *
	 * @param font_id
	 *   Font map identifier (path relative to data/tileset directory).
	 * @return
	 *   Reference to font map or `null` if not configured.
	 */
	FontMap* get(std::string font_id);

	/**
	 * Builds a text sprite.
	 *
	 * @param font_map
	 *   Reference font map.
	 * @param text
	 *   Text for sprite to represent.
	 * @return
	 *   `Sprite` representing a line of text or `null` if font map reference is undefined.
	 */
	Sprite* buildTextSprite(FontMap* font_map, std::string text);
};

#endif /* RRE_FONT_MAP_STORE */
