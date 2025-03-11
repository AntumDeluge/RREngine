/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#ifndef RRE_SCENE_STORE
#define RRE_SCENE_STORE

#include <string>

#include "Scene.h"


/**
 * Functions for loading & retrieving scene data.
 *
 * TODO: rename to SceneFactory
 */
namespace SceneStore {

	/**
	 * Caches filename paths for all scenes.
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

#endif /* RRE_SCENE_STORE */
