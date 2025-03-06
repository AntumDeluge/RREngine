/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <unordered_map>

using namespace std;

#include "Filesystem.h"
#include "Logger.h"
#include "Path.h"
#include "SceneStore.h"


// TODO: rename to SceneStore

namespace SceneStore {
	// FIXME: can't initialize logger here
	//~ Logger* logger = Logger::getLogger("SceneStore");

	bool loaded = false;

	unordered_map<string, string> scene_paths;
	// scene data cached in memory
	unordered_map<string, Scene*> scenes;
};

bool SceneStore::load() {
	Logger* logger = Logger::getLogger("SceneStore");

	if (SceneStore::loaded) {
		logger->warn("Scene paths already loaded");
		return true;
	}

	string dir_scene = Path::rabs("data/scene");
	if (!filesystem::is_directory(dir_scene)) {
		logger->warn("Scene data directory not found: " + dir_scene);
	} else {
		for (filesystem::directory_entry item: Filesystem::listDir(dir_scene, true)) {
			string p = item.path().string();
			if (!item.is_regular_file() || !p.ends_with(".tmx")) {
				continue;
			}
			int d_len = dir_scene.length();
			string id = p.substr(d_len + 1, p.length() - d_len - 5); // @suppress("Invalid arguments")
			SceneStore::scene_paths[id] = p;

#if RRE_DEBUGGING
			logger->debug("Loaded scene path with ID \"" + id + "\" (" + p + ")");
#endif
		}
	}

	SceneStore::loaded = true;
	return true;
}

Scene* SceneStore::loadScene(string id) {
	if (SceneStore::scenes.find(id) != SceneStore::scenes.end()) {
		return SceneStore::scenes[id];
	}

	// TODO: parse scene data from TMX & load into viewport
	return nullptr;
}
