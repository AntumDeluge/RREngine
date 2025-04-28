/* Copyright © 2025 Jordan Irwin <antumdeluge@gmail.com>
 *
 * This work is licensed under the terms of the MIT license.
 * See: LICENSE.txt
 */

#include <algorithm> // std::find, std::max, std::min

#include "Scene.hpp"
#include "SingletonRepo.hpp"
#include "enum/MomentumDir.hpp"

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

void Scene::render(Renderer* ctx) {
	if (s_background2) {
		s_background2->render(ctx, offset_x, offset_y);
	}
	if (s_background) {
		s_background->render(ctx, offset_x, offset_y);
	}

	// TODO: build layers as single image instead of drawing each tile individually
	renderTileLayer(ctx, background);
	renderTileLayer(ctx, terrain);
	renderTileLayer(ctx, collision);

	// TODO: render other layers behind objects

	for (Object* obj: this->objects) {
		obj->render(ctx);
	}
	// player instance not in object list
	if (player != nullptr) {
		player->render(ctx);
	}

	renderTileLayer(ctx, foreground);

	if (s_foreground) {
		s_foreground->render(ctx, offset_x, offset_y);
	}
}

void Scene::renderTileLayer(Renderer* ctx, LayerDefinition ldef) {
	int32_t g_offset_x = 0, g_offset_y = 0;
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

			ctx->drawImage(tileset, index_x*tile_width, index_y*tile_height, tile_width, tile_height,
					g_offset_x - offset_x, g_offset_y - offset_y);
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
	small_rect.w = max<int32_t>(rect.w / tile_width, 1);
	small_rect.h = max<int32_t>(rect.h / tile_height, 1);

	// FIXME: collision recognized late

	// position of bottom of entity
	int32_t pos_y = small_rect.y + small_rect.h + 1;
	// check entire width of entity
	for (int32_t pos_x = small_rect.x; pos_x < small_rect.x + small_rect.w; pos_x++) {
		if (collision_map[pos_x][pos_y]) {
			return true;
		}
	}
	return false;
}

bool Scene::collidesWall(uint8_t dir, SDL_Rect rect) {
	const bool use_left = dir & MomentumDir::LEFT;

	// downscale to match collision map
	SDL_Rect small_rect;
	small_rect.x = rect.x / tile_width;
	small_rect.y = rect.y / tile_height;
	small_rect.w = max<int32_t>(rect.w / tile_width, 1);
	small_rect.h = max<int32_t>(rect.h / tile_height, 1);

	// position at side of entity
	int32_t pos_x = small_rect.x;
	if (!use_left) {
		pos_x += small_rect.w;
		if (pos_x - 1 < 0) {
			// left edge of scene is collision
			// FIXME: doesn't work
			return true;
		}
	} else if (pos_x + 1 > width / tile_width) {
		// right edge of scene is collision
		// FIXME: doesn't work
		return true;
	}
	// check entire height of entity
	for (int32_t pos_y = small_rect.y; pos_y < small_rect.y + small_rect.h; pos_y++) {
		// FIXME: should be looking at neighbor tile
		// int32_t x = use_left ? pos_x - 1 : pos_x + 1;
		if (collision_map[pos_x][pos_y]) {
			return true;
		}
	}
	return false;
}
