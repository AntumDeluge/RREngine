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
	 * @param fid
	 *   Font map identifier.
	 * @param fmap
	 *   Font map instance.
	 */
	void addMap(std::string fid, FontMap* fmap);

	FontMap* getMap(std::string fid);

	Sprite* buildTextSprite(FontMap* fmap, std::string text);
};

#endif /* RRE_FONT_STORE_H */
