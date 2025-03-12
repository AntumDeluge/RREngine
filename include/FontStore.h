/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_STORE_H
#define RRE_FONT_STORE_H

#include <string>

#include "FontMap.h"
#include "Sprite.h"


/**
 * Caches font mappings from configuration.
 *
 * TODO:
 * - rename to FontMapStore
 * - rename file to FontMapStore.hpp
 */
namespace FontStore {

	/**
	 * Caches a font mapping.
	 *
	 * @param font_id
	 *   Font map identifier.
	 * @param font_map
	 *   Font map instance.
	 */
	void addMap(std::string font_id, FontMap* font_map);

	/**
	 * Retrieves a cached font mapping.
	 *
	 * @param font_id
	 *   Font map identifier (path relative to data/tileset directory).
	 * @return
	 *   Reference to font map or `null` if not configured.
	 */
	FontMap* getMap(std::string font_id);

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

#endif /* RRE_FONT_STORE_H */
