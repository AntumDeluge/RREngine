/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_LOADER_H
#define RRE_FONT_MAP_LOADER_H


/**
 * Caches font maps from configuration.
 *
 * TODO:
 * - rename to FontMapFactory
 * - rename file to FontMapFactory.hpp
 */
namespace FontMapLoader {

	/**
	 * Loads configured font maps from built-in data.
	 *
	 * @return
	 *   `true` if loading completed without errors.
	 */
	bool loadBuiltin();

	/**
	 * Loads configured font maps from configuration in `data/conf/fonts.xml`.
	 *
	 * @return
	 *   `true` if loading completed without errors.
	 */
	bool loadConfig();
};

#endif /* RRE_FONT_MAP_LOADER_H */
