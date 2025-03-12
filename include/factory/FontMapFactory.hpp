/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_FONT_MAP_FACTORY
#define RRE_FONT_MAP_FACTORY


/**
 * Caches font maps from configuration.
 */
namespace FontMapFactory {

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

#endif /* RRE_FONT_MAP_FACTORY */
