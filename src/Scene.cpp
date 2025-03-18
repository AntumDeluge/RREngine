/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <algorithm> // std::find

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

void Scene::render(ViewportRenderer* viewport) {
	// TODO: build layers as single image instead of drawing each tile individually
	renderTileLayer(viewport, background);
	renderTileLayer(viewport, terrain);
	renderTileLayer(viewport, collision);

	// TODO: render other layers behind objects

	for (Object* obj: this->objects) {
		obj->render(viewport);
	}

	renderTileLayer(viewport, foreground);

	// TODO: render other layers in front of objects
}

void Scene::renderTileLayer(ViewportRenderer* viewport, LayerDefinition ldef) {
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
	}
}
