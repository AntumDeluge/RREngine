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

	FontMap* getMap(std::string font_id);

	Sprite* buildTextSprite(FontMap* font_map, std::string text);
};

#endif /* RRE_FONT_STORE_H */
