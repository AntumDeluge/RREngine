/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

using namespace std;

#include "Filesystem.h"
#include "Logger.h"
#include "Path.h"
#include "TilesetStore.h"


namespace TilesetStore {
	// FIXME: can't instantiate logger here
	//~ Logger logger = Logger::getLogger("TilesetStore");

	bool loaded = false;

	unordered_map<string, string> tileset_paths;

	unordered_map<string, Tileset*> tilesets;
};

bool TilesetStore::load() {
	Logger logger = Logger::getLogger("TilesetStore");

	if (TilesetStore::loaded) {
		logger.warn("Tileset data already loaded");
		return true;
	}

	string dir_tileset = Path::rabs("data/tileset");
	if (!filesystem::is_directory(dir_tileset)) {
		logger.warn("Tileset data directory not found: " + dir_tileset);
	} else {
		for (filesystem::directory_entry item: Filesystem::listDir(dir_tileset, true)) {
			string p = item.path().string();
			if (!item.is_regular_file() || !p.ends_with(".png")) {
				continue;
			}
			int d_len = dir_tileset.length();
			string id = p.substr(d_len + 1, p.length() - d_len - 5); // @suppress("Invalid arguments")
			TilesetStore::tileset_paths[id] = p;

#if RRE_DEBUGGING
			logger.debug("Loaded tileset path with ID \"" + id + "\" (" + p + ")");
#endif
		}
	}

	TilesetStore::loaded = true;
	return TilesetStore::loaded;
}

Tileset* TilesetStore::getTileset(string rpath) {
	Logger logger = Logger::getLogger("TilesetStore");

	if (TilesetStore::tilesets.find(rpath) != TilesetStore::tilesets.end()) {
#if RRE_DEBUGGING
		logger.debug("Loading cached tileset: " + rpath);
#endif
		return TilesetStore::tilesets[rpath];
	}

#if RRE_DEBUGGING
	logger.debug("Building new tileset: " + rpath);
#endif

	if (TilesetStore::tileset_paths.find(rpath) != TilesetStore::tileset_paths.end()) {
		string t_path = TilesetStore::tileset_paths[rpath];

		// TODO: need to get configured tileset dimensions to build new tileset
		return nullptr;
	}

	logger.warn("Tileset not found: " + rpath);
	return nullptr;
}
