/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <algorithm> // std::find, std::max, std::min

#include "Scene.hpp"
#include "SingletonRepo.hpp"

using namespace std;


Logger Scene::logger = Logger::getLogger("Scene");

void Scene::setLayerCollision(LayerDefinition ldef) {
	collision = ldef;

	uint32_t offset_x = 0, offset_y = 0;
	for (TileDefinition tdef: collision) {
		// global IDs start at 1, not 0
		if (tdef.first > 0) {
			setCollisionPoint(offset_x, offset_y);
		}

		offset_x++;
		if (offset_x * tile_width >= width) {
			offset_y++;
			offset_x = 0;
		}
	}
}

void Scene::logic() {
	if (player) {
		player->logic();
	}
	for (Object* obj: objects) {
		obj->logic();
	}
}

void Scene::render(ViewportImpl* viewport) {
	// TODO: build layers as single image instead of drawing each tile individually
	renderTileLayer(viewport, background);
	renderTileLayer(viewport, terrain);
	renderTileLayer(viewport, collision);

	// TODO: render other layers behind objects

	for (Object* obj: this->objects) {
		obj->render(viewport);
	}
	// player instance not in object list
	if (player != nullptr) {
		player->render(viewport);
	}

	renderTileLayer(viewport, foreground);

	// TODO: render other layers in front of objects
}

void Scene::renderTileLayer(ViewportImpl* viewport, LayerDefinition ldef) {
	uint32_t g_offset_x = 0, g_offset_y = 0;
	for (TileDefinition tdef: ldef) {
		Tileset* tileset = nullptr;
		// find tileset with matching GID
		for (Tileset* t: tilesets) {
			if (tdef.first >= t->getFirstGID() && tdef.first <= t->getLastGID()) {
				tileset = t;
				break;
			}
		}

		if (tileset != nullptr) {
			uint32_t tile_index = tdef.first - tileset->getFirstGID();
			uint32_t cols = tileset->getWidth() / tile_width;
			uint32_t index_x = tile_index % cols;
			uint32_t index_y = tile_index / cols;

			viewport->drawImage(tileset, index_x*tile_width, index_y*tile_height, tile_width, tile_height, g_offset_x, g_offset_y);
		}

		g_offset_x += tile_width;
		if (g_offset_x >= width) {
			g_offset_y += tile_height;
			g_offset_x = 0;
		}
	}
}


void Scene::addObject(Object* obj) {
	obj->setId(next_object_id);
	objects.push_back(obj);
	// increment for next object to be added
	next_object_id++;
	obj->onAdded(this);
}

void Scene::removeObject(Object* obj) {
	auto e_end = this->objects.end();
	auto it = find(this->objects.begin(), e_end, obj);
	if (it != e_end) {
		this->objects.erase(it);
		obj->onRemoved();
	}
}

void Scene::addPlayer(Player* player) {
	player->setId(next_object_id);
	this->player = player;
	// increment for next object to be added
	next_object_id++;
	player->onAdded(this);
}

float Scene::getGravity(uint32_t x, uint32_t y) {
	// TODO: check gravity at given position
	if (has("base_gravity")) {
		return getFloat("base_gravity");
	}
	return 1.0;
}

bool Scene::collidesGround(SDL_Rect rect) {
	// downscale to match collision map
	SDL_Rect small_rect;
	small_rect.x = rect.x / tile_width;
	small_rect.y = rect.y / tile_height;
	small_rect.w = max<uint32_t>(rect.w / tile_width, 1);
	small_rect.h = max<uint32_t>(rect.h / tile_height, 1);

	// position of bottom of entity
	uint32_t pos_y = small_rect.y + small_rect.h;
	// check entire width of entity
	for (int pos_x = small_rect.x; pos_x < small_rect.x + small_rect.w; pos_x++) {
		if (collision_map[pos_x][pos_y]) {
			return true;
		}
	}
	return false;
}

bool Scene::collidesWall(uint8_t dir, SDL_Rect rect) {
	// TODO:
	return false;
}
