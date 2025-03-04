
/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_TMX_LOADER
#define RRE_TMX_LOADER

#include <string>

#include "Scene.h"


// TODO: rename to "SceneStore" or "TMXStore"
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
	 * Loads & returns a scene.
	 *
	 * TODO: need a function to delete cached scene data from memory
	 *
	 * @param id
	 *   Scene idenifier.
	 * @return
	 *   New or cached scene data.
	 */
	Scene* loadScene(std::string id);
};

#endif /* RRE_TMX_LOADER */
