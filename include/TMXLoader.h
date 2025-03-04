
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_TMX_LOADER
#define RRE_TMX_LOADER

#include <string>


namespace TMXLoader {

	/**
	 * Caches filename paths for all scenes.
	 *
	 * TODO: rename to loadPaths
	 *
	 * @return
	 *   `true` if caching succeeded.
	 */
	bool load();

	/**
	 * Loads a scene into the viewport.
	 *
	 * @param id
	 *   Scene idenifier.
	 * @return
	 *   `true` if scene loaded.
	 */
	bool loadScene(std::string id);
};

#endif /* RRE_TMX_LOADER */
