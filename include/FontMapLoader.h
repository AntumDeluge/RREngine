/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_LOADER_H
#define RRE_FONT_MAP_LOADER_H


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
};

#endif /* RRE_FONT_MAP_LOADER_H */
