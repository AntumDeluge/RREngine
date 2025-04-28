/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include "config.h"

#include <cstdint> // *int*_t
#include <unordered_map>

#include <tmxlite/ImageLayer.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/Property.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Types.hpp>

#include "Filesystem.hpp"
#include "LayerDefinition.hpp"
#include "Logger.hpp"
#include "Path.hpp"
#include "TextureLoader.hpp"
#include "Tileset.hpp"
#include "store/SceneStore.hpp"

using namespace std;

// DEBUG:
#include "Entity.hpp"
#include "Player.hpp"
#include "reso.hpp"
#include "store/EntityStore.hpp"


static Logger logger = Logger::getLogger("SceneStore");

namespace SceneStore {
	bool loaded = false;

	unordered_map<string, string> scene_paths;
	// scene data cached in memory
	unordered_map<string, Scene*> scenes;
};

bool SceneStore::load() {
	if (SceneStore::loaded) {
		logger.warn("Scene paths already loaded");
		return true;
	}

	string dir_scene = Path::rabs("data/scene");
	if (!filesystem::is_directory(dir_scene)) {
		logger.warn("Scene data directory not found: ", dir_scene);
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
			logger.debug("Loaded scene path with ID \"", id, "\" (", p, ")");
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

	// get map file path
	string map_path;
	if (SceneStore::scene_paths.find(id) == SceneStore::scene_paths.end()) {
		logger.warn("Scene not found: ", id);
		return nullptr;
	}
	map_path = SceneStore::scene_paths[id];

	tmx::Map map;
	if (!map.load(map_path)) {
		logger.error("Failed to load scene map: ", map_path);
		return nullptr;
	}

	tmx::FloatRect bounds = map.getBounds();
	Scene* scene = new Scene(bounds.width, bounds.height, map.getTileSize().x, map.getTileSize().y);

	// parse tilesets
	for (tmx::Tileset ts: map.getTilesets()) {
		string image_path = Path::norm(ts.getImagePath());

#ifdef RRE_DEBUGGING
		logger.debug("Loading tileset: ", ts.getName(), " (", image_path, ")");
#endif

		SDL_Texture* texture = TextureLoader::absLoad(image_path);
		if (texture == nullptr) {
			logger.error("Failed to load tileset: ", image_path);
			continue;
		}

		scene->addTileset(new Tileset(texture, ts.getFirstGID(), ts.getLastGID()));
	}

	// parse layers
	// TODO:
	// - _maybe_ use layer order instead of names to determine destination
	// - use properties to set parallax backgrounds
	for (auto& layerPtr: map.getLayers()) {
		tmx::Layer& layer = *layerPtr;
		string layerName = layer.getName();

		if (!layer.getVisible()) {
			logger.warn("Layer not visible: ", layerName);
			continue;
		}

		if (layer.getType() == tmx::Layer::Type::Image) {
			tmx::ImageLayer i_layer = dynamic_cast<const tmx::ImageLayer&>(*layerPtr);
			string texture_path = i_layer.getImagePath();
			if (texture_path.empty()) {
				logger.warn("Image layer \"", layerName, "\" without image");
				continue;
			}

			ParallaxImage* p_image = new ParallaxImage(TextureLoader::absLoad(texture_path));
			for (tmx::Property prop: i_layer.getProperties()) {
				if (prop.getName() == "scroll_rate" && prop.getType() == tmx::Property::Type::Float) {
					p_image->setScrollRate(prop.getFloatValue());
					break;
				}
			}

			if (layerName == "s_background") {
				scene->setLayerSBackground(p_image);
			} else if (layerName == "s_background2") {
				scene->setLayerSBackground2(p_image);
			} else if (layerName == "s_foreground") {
				scene->setLayerSForeground(p_image);
			} else {
				logger.warn("Unknown image layer \"", layerName, "\": ", map_path);
				delete p_image;
			}
		} else if (layer.getType() == tmx::Layer::Type::Tile) {
			tmx::TileLayer t_layer = dynamic_cast<const tmx::TileLayer&>(*layerPtr);

			LayerDefinition ldef;
			for (tmx::TileLayer::Tile tile: t_layer.getTiles()) {
				ldef.push_back(TileDefinition(tile.ID, tile.flipFlags));
			}

			if (layerName == "background") {
				scene->setLayerBackground(ldef);
			} else if (layerName == "terrain") {
				scene->setLayerTerrain(ldef);
			} else if (layerName == "objects") {
				scene->setLayerObjects(ldef);
			} else if (layerName == "collision") {
				scene->setLayerCollision(ldef);
			} else if (layerName == "foreground") {
				scene->setLayerForeground(ldef);
			} else {
				logger.warn("Unknown tile layer \"", layerName, "\": ", map_path);
			}
		}
	}

	// DEBUG: test drawing entity in scene
	uint32_t center_x = NATIVE_RES.first / 2; // - (player->getRect().w / 2);
	uint32_t center_y = NATIVE_RES.second / 2; // + (player->getRect().h / 2);
	// NOTE: deleted by scene
	// FIXME:
	// - scene shouldn't inherently add player
	Player* player = new Player(EntityStore::getPlayer("player"));
	player->setX(center_x - (player->getRect().w / 2));
	player->setY(center_y + (player->getRect().h / 2) - 64);
	scene->addPlayer(player);

	// DEBUG:
	Entity* enemy = new Entity(EntityStore::get("enemy"));
	if (!enemy->equals(NullEntity)) {
		enemy->setX(center_x+64);
		enemy->setY(center_y-64);
		scene->addObject(enemy);
	}
	Entity* f_enemy = new Entity(EntityStore::get("flying_enemy"));
	if(!f_enemy->equals(NullEntity)) {
		f_enemy->setX(center_x+30);
		f_enemy->setY(center_y-64);
		scene->addObject(f_enemy);
	}

	// cache for subsequent retrieval
	SceneStore::scenes[id] = scene;
	return scene;
}
