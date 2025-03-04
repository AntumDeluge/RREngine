
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
#include "TMXLoader.h"


// TODO: rename to SceneStore

namespace TMXLoader {
	// FIXME: can't initialize logger here
	//~ Logger* logger = Logger::getLogger("TMXLoader");

	bool loaded = false;

	unordered_map<string, string> scene_paths;
	// scene data cached in memory
	unordered_map<string, Scene*> scenes;
};

bool TMXLoader::load() {
	if (TMXLoader::loaded) {
		//~ TMXLoader::logger->warn("Scene paths already loaded");
		Logger::getLogger("TMXLoader")->warn("Scene paths already loaded");
		return true;
	}

	string dir_scene = Path::rabs("data/scene");

	for (filesystem::directory_entry item: Filesystem::listDir(dir_scene, true)) {
		string p = item.path().string();
		if (!item.is_regular_file() || !p.ends_with(".tmx")) {
			continue;
		}
		int d_len = dir_scene.length();
		string id = p.substr(d_len + 1, p.length() - d_len - 5);
		TMXLoader::scene_paths[id] = p;

#if RRE_DEBUGGING
		//~ TMXLoader::logger->debug("Loaded scene path with ID \"" + id + "\" (" + p + ")");
		Logger::getLogger("TMXLoader")->debug("Loaded scene path with ID \"" + id + "\" (" + p + ")");
#endif
	}

	TMXLoader::loaded = true;
	return true;
}

Scene* TMXLoader::loadScene(string id) {
	if (TMXLoader::scenes.find(id) != TMXLoader::scenes.end()) {
		return TMXLoader::scenes[id];
	}

	// TODO: parse scene data from TMX & load into viewport
	return nullptr;
}
