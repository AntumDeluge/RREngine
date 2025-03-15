/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <cstddef> // size_t
#include <unordered_map>

#include <tmxlite/Map.hpp>

#include "Filesystem.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "TextureLoader.hpp"
#include "Tileset.hpp"
#include "store/SceneStore.hpp"

using namespace std;

// DEBUG:
#include "Entity.hpp"
#include "store/EntityStore.hpp"


namespace SceneStore {
	// FIXME: can't initialize logger here
	//~ Logger logger = Logger::getLogger("SceneStore");

	bool loaded = false;

	unordered_map<string, string> scene_paths;
	// scene data cached in memory
	unordered_map<string, Scene*> scenes;
};

bool SceneStore::load() {
	Logger logger = Logger::getLogger("SceneStore");

	if (SceneStore::loaded) {
		logger.warn("Scene paths already loaded");
		return true;
	}

	string dir_scene = Path::rabs("data/scene");
	if (!filesystem::is_directory(dir_scene)) {
		logger.warn("Scene data directory not found: " + dir_scene);
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
			logger.debug("Loaded scene path with ID \"" + id + "\" (" + p + ")");
#endif
		}
	}

	SceneStore::loaded = true;
	return true;
}

Scene* SceneStore::get(string id) {
	// look in cache first
	if (SceneStore::scenes.find(id) != SceneStore::scenes.end()) {
		return SceneStore::scenes[id];
	}

	Logger logger = Logger::getLogger("SceneStore");

	// get map file path
	string map_path;
	if (SceneStore::scene_paths.find(id) == SceneStore::scene_paths.end()) {
		logger.warn("Scene not found: " + id);
		return nullptr;
	}
	map_path = SceneStore::scene_paths[id];

	tmx::Map map;
	if (!map.load(map_path)) {
		logger.error("Failed to load scene map: " + map_path);
		return nullptr;
	}

	Scene* scene = new Scene(map.getTileSize().x, map.getTileSize().y);
	// TODO: get map dimensions
	//auto map_size = map.getSize();
	size_t width = 0;
	size_t height = 0;

	// parse tilesets
	for (tmx::Tileset ts: map.getTilesets()) {
		string image_path = Path::norm(ts.getImagePath());

#ifdef RRE_DEBUGGING
		logger.debug("Loading tileset: " + ts.getName() + " (" + image_path + ")");
#endif

		SDL_Texture* texture = TextureLoader::absLoad(image_path);
		if (texture == nullptr) {
			logger.error("Failed to load tileset: " + image_path);
			continue;
		}

		scene->addTileset(Tileset(texture, ts.getFirstGID(), ts.getLastGID()));
	}

	// parse layers
	// TODO:
	// - _maybe_ use layer order instead of names to determine destination
	// - use properties to set parallax backgrounds
	for (auto& layerPtr: map.getLayers()) {
		tmx::Layer& layer = *layerPtr;
		string layerName = layer.getName();

		if (layer.getType() == tmx::Layer::Type::Image) {
			tmx::ImageLayer i_layer = dynamic_cast<const tmx::ImageLayer&>(*layerPtr);

			if (layerName == "s_background") {
				scene->setLayerSBackground(&i_layer);
			} else if (layerName == "s_background2") {
				scene->setLayerSBackground2(&i_layer);
			} else if (layerName == "s_foreground") {
				scene->setLayerSForeground(&i_layer);
			} else {
				logger.warn("Unknown image layer \"" + layerName + "\": " + map_path);
			}
		} else if (layer.getType() == tmx::Layer::Type::Tile) {
			tmx::TileLayer t_layer = dynamic_cast<const tmx::TileLayer&>(*layerPtr);

			if (layerName == "background") {
				scene->setLayerBackground(&t_layer);
			} else if (layerName == "terrain") {
				scene->setLayerTerrain(&t_layer);
			} else if (layerName == "objects") {
				scene->setLayerObjects(&t_layer);
			} else if (layerName == "collision") {
				scene->setLayerCollision(&t_layer);
			} else if (layerName == "foreground") {
				scene->setLayerForeground(&t_layer);
			} else {
				logger.warn("Unknown tile layer \"" + layerName + "\": " + map_path);
			}
		}
	}

	// DEBUG: test drawing entity in scene
	// NOTE: deleted by scene
	// FIXME:
	// - scene shouldn't inherently add player
	scene->addObject(new Entity(EntityStore::get("player")));

	// cache for subsequent retrieval
	SceneStore::scenes[id] = scene;
	return scene;
}
